target_sources(wxTheme PRIVATE
	"button.h" "checkbox.h" "dataviewtree.h" "dialog.h" "hyperlink.h" "label.h"
	"list.h" "menu.h" "panel.h" "propertygrid.h" "staticbox.h" "statusbar.h"
	"text.h" "theme.h" "toolbar.h" "treelist.h" "utils.h"
    "control.h" "language.h" "combobox.h" "staticline.h" "renderers.h")

if(${WXT_EXT_TERMINALCTRL})
	target_sources(wxTheme PRIVATE "ext/terminalctrl.h")
endif()