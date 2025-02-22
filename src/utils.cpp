#include "wxt/utils.h"

namespace wxt
{
    // Wrapper

    Wrapper::Wrapper(wxWindow* win, const wxString& text, int widthMax)
    {
        Wrap(win, text, widthMax);
    }

    const std::vector<wxString>& Wrapper::getLines() const
    {
        return this->lines;
    }

    wxString Wrapper::getText() const
    {
        wxString text;
        for (wxString line : lines)
            text += line + "\n";
        return text;
    }

    void Wrapper::OnOutputLine(const wxString& line)
    {
        this->lines.push_back(line);
    }

    // Utils

    wxPoint calcOriginPoint(const wxSize& containerSize, const wxSize& childSize)
    {
        wxSize size(containerSize / 2 - childSize / 2);
        return wxPoint(size.x, size.y);
    }

    wxWindow* GetTopParent(wxWindow* pWindow)
    {
        wxWindow* pWin = pWindow;
        while (true)
        {
            if (pWin->GetParent())
                pWin = pWin->GetParent();
            else
                break;
        }
        return pWin;
    }
}