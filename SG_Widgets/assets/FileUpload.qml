import QtQuick
import QtQuick.Dialogs

FileDialog{
	property string selectedFilePath: ""
	objectName: "0"
	fileMode: FileDialog.OpenFile
	
	function sendAcceptedSignal(){
		selectedFilePath = this.selectedFile;
		objectName = "1";
	}
	
	function sendRejectedSignal(){
		selectedFilePath = "";
		objectName = "2";
	}
	
	onAccepted: sendAcceptedSignal()
	onRejected: sendRejectedSignal();
}
