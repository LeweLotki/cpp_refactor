#include "stream.hpp"

namespace filesystem  = boost::filesystem;

Stream::Stream()
{
    device_id = 0;
    api_id = cv::CAP_ANY;
    frame_count = 0;
}

void Stream::run(const std::string& mode, filesystem::path output_dir, int frame_limit)
{
    this->output_dir = output_dir;
    this->frame_limit = frame_limit;

    switch ( resolve_mode(mode) )
    {
        case DISPLAY_MODE:
            this -> display_mode();
            break;
        case SAVE_MODE:
            this -> save_mode();
            break;
        case SAVE_DISPLAY_MODE:
            this -> save_display_mode();
            break;
        case VOID_MODE:
            this -> void_mode();
            break;
        case INVALID_MODE:
            std::cerr << "ERROR: incorrect mode chosen.";
            break;
        default:
            std::cerr << "ERROR: incorrect mode chosen.";
            break;
    }
}

void Stream::display_mode()
{
    bool frame_saved = false;
    bool save_mode = false;
    bool ret;
    cv::Mat frame;

    if (frame_limit < 1) { frame_limit = -1; }

    this->open_camera();

    while(frame_limit == -1 || frame_limit > frame_count)
    {
        cap.read(frame);
        
        if (frame.empty())
        {
            std::cerr << "ERROR! empty image\n";
            break;
        }

        imshow("stream", frame);

        this->frame = frame; 
        this -> notify_observers(this->frame);

        if ((char)cv::waitKey(29) == (char)ESC_KEY) { break; } 
        if (frame_limit != -1 && ((char)cv::waitKey(31) == (char)s_KEY || save_mode)) 
        {
            if (!frame_saved)
            {
                this -> create_output_dir();
                this->resolution[0] = frame.cols;
                this->resolution[1] = frame.rows;
                frame_saved = true;
                save_mode = true;
            }
            this -> save_images(frame);
        }
        frame_count += 1;
    }
}

void Stream::save_display_mode()
{
    bool ret;
    bool first_iter = true;
    cv::Mat frame;
    this -> create_output_dir();

    this->open_camera();

    if (frame_limit < 1) { frame_limit = (int)1e3; }

    while(frame_limit > frame_count)
    {
        cap.read(frame);
        
        if (frame.empty())
        {
            std::cerr << "ERROR! empty image\n";
            break;
        }

        imshow("stream", frame);

        this->frame = frame; 
        this -> notify_observers(this->frame);

        if ((char)cv::waitKey(29) == (char)ESC_KEY) { break; } 
        
        if (first_iter)
        {
            this->resolution[0] = frame.cols;
            this->resolution[1] = frame.rows;
            first_iter = false;
        }
        this -> save_images(frame);
        frame_count += 1;
    }
}

void Stream::save_mode()
{
    bool ret;
    bool first_iter = true;
    cv::Mat frame;
    this -> create_output_dir();

    this->open_camera();

    if (frame_limit < 1) { frame_limit = (int)1e3; }

    while(frame_limit > frame_count)
    {
        cap.read(frame);
        
        if (frame.empty())
        {
            std::cerr << "ERROR! empty image\n";
            break;
        }
        
        this->frame = frame;
        this -> notify_observers(this->frame);
       
        if ((char)cv::waitKey(29) == (char)ESC_KEY) { break; } 
        
        if (first_iter)
        {
            this->resolution[0] = frame.cols;
            this->resolution[1] = frame.rows;
            first_iter = false;
        }
        this -> save_images(frame);
        frame_count += 1;
    }
}

void Stream::void_mode()
{
    bool frame_saved = false;
    bool save_mode = false;
    bool ret;
    cv::Mat frame;

    if (frame_limit < 1) { frame_limit = -1; }

    this->open_camera();

    while(frame_limit == -1 || frame_limit > frame_count)
    {
        cap.read(frame);
        
        if (frame.empty())
        {
            std::cerr << "ERROR! empty image\n";
            break;
        }

        this->frame = frame; 
        this -> notify_observers(this->frame);
       
        if ((char)cv::waitKey(29) == (char)ESC_KEY) { break; } 
        if (frame_limit != -1 && ((char)cv::waitKey(31) == (char)s_KEY || save_mode)) 
        {
            if (!frame_saved)
            {
                this -> create_output_dir();
                this->resolution[0] = frame.cols;
                this->resolution[1] = frame.rows;
                frame_saved = true;
                save_mode = true;
            }
            this -> save_images(frame);
        }
        frame_count += 1;
    }
}

cv::Mat Stream::get_current_frame() const 
{
    std::lock_guard<std::mutex> lock(this->frame_mutex);
    return this->frame.clone();
}

void Stream::open_camera()
{
    cap = cv::VideoCapture(device_id + api_id);

    if (!cap.isOpened())
    {
        std::cerr << "ERROR! Unable to open camera\n";
    }
}

void Stream::set_resolution(int* resolution[])
{
    this->resolution[0] = *resolution[0];
    this->resolution[1] = *resolution[1];
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, this->resolution[0]);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, this->resolution[1]);
}

void Stream::create_output_dir()
{
    if (filesystem::exists(this->output_dir))
    {
        filesystem::remove_all(this->output_dir);
    }
    filesystem::create_directory(this->output_dir);
    this->left_dir = this->output_dir / "L";
    this->right_dir = this->output_dir / "R";
    filesystem::create_directory(this->left_dir);
    filesystem::create_directory(this->right_dir);
}

void Stream::save_images(cv::Mat frame)
{
    std::string filename_left = (this->left_dir / (std::to_string(this->frame_count) + ".png")).string();
    std::string filename_right = (this->right_dir / (std::to_string(this->frame_count) + ".png")).string();

    std::vector<cv::Mat> frames = this -> subdivide_camera_image(frame);

    cv::imwrite(filename_left, frames[0]);
    cv::imwrite(filename_right, frames[1]);
}

std::vector<cv::Mat> Stream::subdivide_camera_image(cv::Mat frame)
{
    cv::Mat frame_left = frame(
        cv::Range(0, resolution[1]), 
        cv::Range(0, (int)(resolution[0] / 2))
    );
    cv::Mat frame_right = frame(
        cv::Range(0, resolution[1]), 
        cv::Range((int)(resolution[0] / 2), resolution[0])
    );
    
    std::vector<cv::Mat> frames { frame_left, frame_right };    

    return frames;
}

Stream::Modes Stream::resolve_mode(const std::string& mode)
{
    static const std::map<std::string, Modes> modes_map {
        { "display_mode", DISPLAY_MODE },
        { "save_mode", SAVE_MODE },
        { "save_display_mode", SAVE_DISPLAY_MODE },
        { "void_mode", VOID_MODE }
    };

    auto itr = modes_map.find(mode);
    if( itr != modes_map.end() ) {
        return itr->second;
    }

    return INVALID_MODE;
}

