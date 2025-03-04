wxTheme
=====
A set of customized widgets with an ability to add themes and easier language support to wxWidgets.
The library uses themes defined in XML files to customize the looks of widgets. In future this will be migrated to CSS files.
The project is still under development. Some controls are not yet supported, and others may not be supported fully. The goal of this project is to fully support all widgets. All support is welcome.

Supported widgets (theme)
=====
- wxFrame
- wxDialog
- wxDataViewIconTextRenderer
- wxLabel
- wxPanel
- wxPropertyGrid
- wxTextCtrl
- [wxWidgetsTerminalCtrl](https://github.com/rwypior/wxWidgetsTerminalCtrl) (optionally)
- wxTreeListCtrl
- wxStaticLine
- Status bar
- Window title bar (Windows only)
- AUI (partial)
- wxMenuBar (partial)
- wxListBox (partial)
- wxCheckBox (partial)
- wxComboBox (partial)
- wxHyperlinkCtrl (partial)
- wxStaticBox (partial)
- wxToolBar (partial)
- wxComboBox (partial)

Usage
=====
When creating your dialogs, simply use widgets provided in wxt namespace instead of default widgets.

In order to enable AUI, status bar and menu bar themes, it is required to put the following code in window's constructor:

```
enableAuiTheming(m_mgr);
enableStatusBarTheming(m_statusBar);
enableMenuBarTheming(m_menubar);
```

TODO
=====
Currently the high-proprity items are:
1. Improve support for partially supported widgets
2. Use CSS instead of XML for themes
3. Add support for more widgets

Example
=====
The project provides an example project showing basic usage of the library.

![wxtheme1](https://github.com/user-attachments/assets/815cf1dd-a838-4c0c-b45e-0a9e834ceec6)
![wxtheme2](https://github.com/user-attachments/assets/6acfa887-d427-4be5-a178-adb97f1fc361)

