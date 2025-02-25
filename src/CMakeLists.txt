target_sources(wxTheme PRIVATE
	"button.cpp" "checkbox.cpp" "dataviewtree.cpp" "dialog.cpp" "hyperlink.cpp"
	"label.cpp" "list.cpp" "menu.cpp" "panel.cpp" "propertygrid.cpp" "staticbox.cpp"
	"statusbar.cpp" "text.cpp" "theme.cpp" "toolbar.cpp" "treelist.cpp" "utils.cpp"
     "language.cpp" "combobox.cpp" "ext/terminalctrl.cpp")

if(${WXT_EXT_TERMINALCTRL})
	target_sources(wxTheme PRIVATE "ext/terminalctrl.cpp")
endif()