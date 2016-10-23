using UnityEngine;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Text;
public class Connection {
	static Socket Server;
	static string ip; 
	static int port;
	static EndPoint servAddr;
	static bool connect;
	static MainLogin mainLoginScript;

	static public void Init(MainLogin sc){
		mainLoginScript = sc;
		Reset ();
	}

	static public void Connect(){
		IPEndPoint ipep = new IPEndPoint (IPAddress.Parse (ip), 0);
		Server = new Socket (AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
		Server.Bind (ipep);
		IPEndPoint servAddrIPEP = new IPEndPoint (IPAddress.Parse (ip), port);
		servAddr = (EndPoint)(servAddrIPEP);
		byte[] data = Encoding.UTF8.GetBytes ("Connect");
		Server.SendTo (data, data.Length, SocketFlags.None, servAddr);

	}



	static public void SetAddress(string _ip, string _port){
		ip = _ip;
		port = int.Parse (_port);
	}

	static public string GetConnectData(){
		
		if (Server.Available != 0) {
			byte[] data = new byte[8192];
			//try {
				int sizeData = Server.Receive (data);
				string s = Encoding.UTF8.GetString (data, 0, sizeData);
				if (!Variables.mainLoginScript.showAllPosts){
					string tem = GetDat(s);
					if(tem != "AllUPD" && tem != "UIUPD"){

					mainLoginScript.PrintS ("RECEIVE: " + sizeData.ToString () +" " + s);
					}
				}
				else{

				mainLoginScript.PrintS ("RECEIVE: " + sizeData.ToString () + " " + s);
				}
				return s;
			//} catch {
			//	return "ConnectLost|";
			//}

		}		
		return "NoneData";

	}

	static public void SetPort(int _port){
		IPEndPoint servAddrIPEP = new IPEndPoint (IPAddress.Parse (ip), _port);
		servAddr = (EndPoint)(servAddrIPEP);
	}

	static public void Send(string mess){
		if (!Variables.mainLoginScript.showAllPosts){
			if(mess != "NeedUPD|" && mess != "NeedUIUPD|"){
				mainLoginScript.PrintS ("SEND: " + mess);
			}
		}
		else{
			mainLoginScript.PrintS ("SEND: " + mess);
		}
		byte[] data = Encoding.UTF8.GetBytes (mess);
		Server.SendTo (data, data.Length, SocketFlags.None, servAddr);
	}

	static public void SetConnect(bool b){
		connect = b;
	}

	static public bool GetConnect(){
		return connect;
	}
	static public void CloseConnect(){

		Server.Close ();
	}
	static public void Reset(){

		if (connect) {
			CloseConnect ();
		}
		connect = false;
	}

	static string GetDat(string mess){

		string s = "";
		if (mess != " ") {
			s = mess.Substring (0, mess.IndexOf ("|"));
		}
		return s;
	}
}
