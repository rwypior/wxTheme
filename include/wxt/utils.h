#ifndef _h_wxtheme_utils
#define _h_wxtheme_utils

#include <wx/wx.h>
#include <wx/textwrapper.h>

#include <vector>
#include <optional>

namespace wxt
{
    template<typename T>
    struct Bitfield
    {
        T value;

        Bitfield(T value) : value(value) {}
        Bitfield(unsigned int value) : value(static_cast<T>(value)) {}
        operator T() const { return value; }
        operator bool() const { return static_cast<unsigned int>(value); }
        Bitfield<T> operator |(T b) { return static_cast<T>(static_cast<unsigned int>(value) | static_cast<unsigned int>(b)); };
        Bitfield<T> operator &(T b) { return static_cast<T>(static_cast<unsigned int>(value) & static_cast<unsigned int>(b)); };
        Bitfield<T> operator |=(T b) { return static_cast<T>(value = static_cast<T>(static_cast<unsigned int>(value) | static_cast<unsigned int>(b))); };
        Bitfield<T> operator &=(T b) { return static_cast<T>(value = static_cast<T>(static_cast<unsigned int>(value) & static_cast<unsigned int>(b))); };
        Bitfield<T> operator ~() { return static_cast<T>(~static_cast<unsigned int>(value)); };
    };

    class Wrapper : public wxTextWrapper
    {
    public:
        Wrapper(wxWindow* win, const wxString& text, int widthMax);
        const std::vector<wxString>& getLines() const;
        wxString getText() const;

    protected:
        void OnOutputLine(const wxString& line) override;

    private:
        std::vector<wxString> lines;
    };

    wxPoint calcOriginPoint(const wxSize& containerSize, const wxSize& childSize);

    wxWindow* GetTopParent(wxWindow* pWindow);
}

// Enable bitwise operations on enum class
// Best to use on namespace-level
#define DEFINE_BITFIELD(Enum) \
	static inline wxt::Bitfield<Enum> operator |(Enum a, Enum b) { return static_cast<unsigned int>(a) | static_cast<unsigned int>(b); } \
	static inline wxt::Bitfield<Enum> operator &(Enum a, Enum b) { return static_cast<unsigned int>(a) & static_cast<unsigned int>(b); } \
    static inline wxt::Bitfield<Enum> operator |=(Enum& a, Enum b) { return a = static_cast<Enum>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b)); } \
	static inline wxt::Bitfield<Enum> operator &=(Enum& a, Enum b) { return a = static_cast<Enum>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b)); } \
    static inline wxt::Bitfield<Enum> operator <<(unsigned int a, Enum b) { return static_cast<Enum>(a << static_cast<unsigned int>(b)); } \
    static inline wxt::Bitfield<Enum> operator >>(unsigned int a, Enum b) { return static_cast<Enum>(a >> static_cast<unsigned int>(b)); } \
    static inline wxt::Bitfield<Enum> operator ~(Enum a) { return static_cast<Enum>(~static_cast<unsigned int>(a)); }

template<typename T>
T either(const std::optional<T>& opt, const T& def)
{
    return opt ? *opt : def;
}

#endif