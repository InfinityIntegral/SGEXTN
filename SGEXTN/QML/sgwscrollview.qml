import QtQuick
import QtQuick.Controls
import ThemeColours 0.0
import Resizer 0.0

ScrollView{
	property bool utc: true
	property int bg: 8
	property color bgc: "#FF00C8"
	property int bs: 4
	property color bsc: "#FF00C8"
	property int fs: 6
	property color fsc: "#FF00C8"
	property int bsh: 3
	property color bshc: "#FF00C8"
	property int fsh: 5
	property color fshc: "#FF00C8"
	property int bsf: 2
	property color bsfc: "#FF00C8"
	property int fsf: 4
	property color fsfc: "#FF00C8"
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property real h1: 0.0
	property real h0: 0.0
	property real i1: 0.0
	property real i0: 0.0
	property real s1: 0.0
	property real s0: 0.0
	property real pw1: 0.0
	property real pw0: 0.0
	property real ph1: 0.0
	property real ph0: 0.0
	
	x: x1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + x0 * Resizer.sizeUnit
	y: y1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + y0 * Resizer.sizeUnit
	width: w1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + w0 * Resizer.sizeUnit
	height: h1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + h0 * Resizer.sizeUnit
	
	ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
	contentWidth: width
	clip: true
	
	function getBg(vutc, vbg, vbgc){
		if(vutc == true){return ThemeColours.getThemeColour(vbg);}
		else{return vbgc;}
	}
	
	function getBS(vutc, vvh, vvf, vbs, vbsc, vbsh, vbshc, vbsf, vbsfc){
		if(vutc == true){
			if(vvf == true){return ThemeColours.getThemeColour(vbsf);}
			else if(vvh == true){return ThemeColours.getThemeColour(vbsh);}
			else{return ThemeColours.getThemeColour(vbs);}
		}
		else{
			if(vvf == true){return vbsfc;}
			else if(vvh == true){return vbshc;}
			else{return vbsc;}
		}
	}
	
	function getFS(vutc, vvh, vvf, vfs, vfsc, vfsh, vfshc, vfsf, vfsfc){
		if(vutc == true){
			if(vvf == true){return ThemeColours.getThemeColour(vfsf);}
			else if(vvh == true){return ThemeColours.getThemeColour(vfsh);}
			else{return ThemeColours.getThemeColour(vfs);}
		}
		else{
			if(vvf == true){return vfsfc;}
			else if(vvh == true){return vfshc;}
			else{return vfsc;}
		}
	}
	
	Column{
		width: parent.width
		
		Rectangle{
			property bool canParent: true
			width: parent.width - (s1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + s0 * Resizer.sizeUnit)
			height: Math.max(h1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + h0 * Resizer.sizeUnit, i1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + i0 * Resizer.sizeUnit)
			color: getBg(utc, bg, bgc)
		}
	}
	
	ScrollBar.vertical: ScrollBar{
		property bool vf: pressed
		property bool vh: hovered
		
		policy: ScrollBar.AlwaysOn
		x: parent.width - width
		y: 0
		width: s1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + s0 * Resizer.sizeUnit
		height: parent.height
		padding: 0
		
		contentItem: Rectangle{
			color: getFS(utc, parent.vh, parent.vf, fs, fsc, fsh, fshc, fsf, fsfc)
			width: parent.width
		}
		background: Rectangle{
			color: getBS(utc, parent.vh, parent.vf, bs, bsc, bsh, bshc, bsf, bsfc)
			width: parent.width
		}
	}
}
