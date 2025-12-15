import QtQuick
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
    x: parent.SafeArea.margins.left
    y: parent.SafeArea.margins.top
    width: parent.width - parent.SafeArea.margins.left - parent.SafeArea.margins.right
    height: parent.height - parent.SafeArea.margins.top - parent.SafeArea.margins.bottom
    color: ThemeColours.getThemeColour(6)
}
