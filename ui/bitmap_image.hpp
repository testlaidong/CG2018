#ifndef INCLUDE_BITMAP_IMAGE_HPP
#define INCLUDE_BITMAP_IMAGE_HPP

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

class bitmap_image
{
public:
   struct rgb_t{ unsigned char red, green, blue; };

   bitmap_image(const unsigned int width, const unsigned int height)
   : width_ (width ), height_(height), row_increment_  (0), bytes_per_pixel_(3)
   {
      create_bitmap();
   }

   inline void set_pixel(const unsigned int x, const unsigned int y, const unsigned char red,
                         const unsigned char green, const unsigned char blue)
   {
      unsigned offset   = y * row_increment_ + x * bytes_per_pixel_;
      data_[offset + 0] = blue;
      data_[offset + 1] = green;
      data_[offset + 2] = red;
   }

   void save_image(const std::string& file_name) const
   {
      std::ofstream stream(file_name.c_str(),std::ios::binary);

      auto bih = bitmap_information_header();

      bih.width            = width_;
      bih.height           = height_;
      bih.bit_count        = static_cast<unsigned short>(bytes_per_pixel_ << 3);
      bih.size             = bih.struct_size();
      bih.size_image       = (((bih.width * bytes_per_pixel_) + 3) & 0x0000FFFC) * bih.height;

      bitmap_file_header bfh;

      bfh.type             = 19778;
      bfh.size             = bfh.struct_size() + bih.struct_size() + bih.size_image;
      bfh.reserved1        = 0;
      bfh.reserved2        = 0;
      bfh.off_bits         = bih.struct_size() + bfh.struct_size();

      write_bfh(stream,bfh);
      write_to_stream(stream,bih);

      unsigned int padding = (4 - ((3 * width_) % 4)) % 4;
      std::cout << padding << std::endl;
      char padding_data[4] = { 0x00, 0x00, 0x00, 0x00 };
      for (unsigned int i = 0; i < height_; ++i)
      {
         const unsigned char* data_ptr = &data_[(row_increment_ * (height_ - i - 1))];
         stream.write(reinterpret_cast<const char*>(data_ptr), sizeof(unsigned char) * bytes_per_pixel_ * width_);
         stream.write(padding_data, padding);
      }

      stream.close();
   }

   inline void set_all_channels(const unsigned char& r_value,
                                const unsigned char& g_value,
                                const unsigned char& b_value)
   {
      for (unsigned char* itr = (data() + 0); itr < end(); itr += bytes_per_pixel_)
      {
         *(itr + 0) = b_value;
         *(itr + 1) = g_value;
         *(itr + 2) = r_value;
      }
   }


   inline unsigned char* data()
   {
      return const_cast<unsigned char*>(data_.data());
   }

private:

   inline unsigned char* end()
   {
      return const_cast<unsigned char*>(data() + data_.size());
   }

   struct bitmap_file_header
   {
      unsigned short type;
      unsigned int   size;
      unsigned short reserved1;
      unsigned short reserved2;
      unsigned int   off_bits;

      unsigned int struct_size() const
      {
         return 14;
      }
   };

   struct bitmap_information_header
   {
      unsigned int   size, width, height;
      unsigned short planes, bit_count;
      unsigned int   compression, size_image, x_pels_per_meter, y_pels_per_meter, clr_used, clr_important;
      bitmap_information_header():planes(1), compression(0),  x_pels_per_meter(0), y_pels_per_meter(0),
          clr_used(0), clr_important(0){}

      unsigned int struct_size() const
      {
         return 40;
      }
   };

   template <typename T>
   inline void write_to_stream(std::ofstream& stream,const T& t) const
   {
      stream.write(reinterpret_cast<const char*>(&t),sizeof(T));
   }

   inline void write_bfh(std::ofstream& stream, const bitmap_file_header& bfh) const
   {
        write_to_stream(stream,bfh.type     );
        write_to_stream(stream,bfh.size     );
        write_to_stream(stream,bfh.reserved1);
        write_to_stream(stream,bfh.reserved2);
        write_to_stream(stream,bfh.off_bits );
   }

   void create_bitmap()
   {
      row_increment_ = width_ * bytes_per_pixel_;
      data_.resize(height_ * row_increment_);
   }

   unsigned int width_;
   unsigned int height_;
   unsigned int row_increment_;
   unsigned int bytes_per_pixel_;
   std::vector<unsigned char> data_;
};

#endif
