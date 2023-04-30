#include <string>

#include <clip/clip.h>

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
        }
    }
}
