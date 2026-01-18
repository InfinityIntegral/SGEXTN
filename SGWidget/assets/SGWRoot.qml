import QtQuick
import ThemeColours 0.0
import Resizer 0.0

Rectangle {
    x: parent?.SafeArea?.margins?.left ?? 0
    y: parent?.SafeArea?.margins?.top ?? 0
    width: (parent?.width ?? 0) - (parent?.SafeArea?.margins?.left ?? 0) - (parent?.SafeArea?.margins?.right ?? 0)
    height: (parent?.height ?? 0) - (parent?.SafeArea?.margins?.top ?? 0) - (parent?.SafeArea?.margins?.bottom ?? 0)
    color: ThemeColours.getThemeColour(3)
}
