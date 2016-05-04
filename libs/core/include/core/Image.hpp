#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <core/Resouce.hpp>

class LIB_EXPORT_CONV Image : public Resource {
public:

    Image(const char* filename, bool flipped=false);
    ~Image();



private:


};

#endif /*__IMAGE_HPP__ */