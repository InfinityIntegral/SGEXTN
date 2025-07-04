import QtQuick 6.9
import QtQuick.Dialogs 6.9

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
