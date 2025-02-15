#include "base/base.hpp"

#include <string>

#include <clip/clip.h>
#include <ZXing/ReadBarcode.h>
#ifdef LIBRARY_DEBUG
    #include <fast_io.h>
#endif

#include "clipboard.hpp"

void clipboard_handle() noexcept
{
    static std::string src_text, replace_text;

    if (clip::has(clip::text_format()))
    {
        std::string text;
        clip::get_text(text);
        if (text.empty())
            return;

        // clip::set_text will be invoked once the clipboard_handle function
        if (text != src_text && text != replace_text)
        {
            src_text = std::move(text);
            std::string clear_url = get_clear_url(src_text);
            if (clear_url.empty())
                return;

            replace_text = std::move(clear_url);
            clip::set_text(replace_text);

#ifdef LIBRARY_DEBUG
            fast_io::io::perrln(replace_text);
#endif
        }
    }
    else if (clip::has(clip::image_format()))
    {
        clip::image src_image;
        if (!clip::get_image(src_image))
            return;

        auto spec = src_image.spec();

#ifdef LIBRARY_DEBUG
        fast_io::io::perrln("image: (", spec.width, ", ", spec.height, ", ", spec.bits_per_pixel, ")");
#endif

        auto format = ZXing::ImageFormat::None;
        if (spec.bits_per_pixel == 32)
        {
            format = ZXing::ImageFormat::RGBA;
        }
        else if (spec.bits_per_pixel == 24)
        {
            format = ZXing::ImageFormat::RGB;
        }
        else
        {
            return;
        }

        auto image = ZXing::ImageView
        {
            reinterpret_cast<u8*>(src_image.data()),
            static_cast<int>(spec.width),
            static_cast<int>(spec.height),
            format,
            static_cast<int>(spec.bytes_per_row),
        };
        auto options = ZXing::ReaderOptions().setFormats(ZXing::BarcodeFormat::Any);
        auto barcodes = ZXing::ReadBarcodes(image, options);

        if (!barcodes.empty())
        {
            auto url = barcodes.cbegin()->text();
            clip::set_text(url);
        }

#ifdef LIBRARY_DEBUG
        for (const auto& b : barcodes)
        {
            fast_io::io::perrln(ZXing::ToString(b.format()), ": ", b.text());
        }
#endif
    }
}
