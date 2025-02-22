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
- wxTreeListCtrl
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

![wxtheme1](https://github.com/user-attachments/assets/acb0f011-f313-49e9-beb9-9d830b0a04e8)
![wxtheme2](https://github.com/user-attachments/assets/f201c722-50b5-407d-8f09-cc1dd0baa7bb)
