package com.psl.iucaa.services;
import java.io.*;
import java.net.*;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;




/**
 * This class sends the Command XML over socket
 * @author swati_jadhav
 *
 */
public class Requester implements Runnable{
	
	private static final Log log = LogFactory.getLog(Requester.class);
	Socket requestSocket;
	OutputStream out;
 	InputStream in;
 	String message="";
 	//PrintWriter pw;
 	//String requestFile="G:/IUCAA/IUCAAGUI/ExpertCommands/CCU_Request.xml";
 	String xmlRequest;
 	String xmlResponse = null;
 	boolean stoprequest = false;
 	boolean responseReceived = false;
 	String errormessage; 	
 	int port = 2000;
 	 	
	Requester(){}
	
	Requester(String xmlRequest){
		this.xmlRequest = xmlRequest;
	}
	
	
	public void run()
	{
		try{
			//1. creating a socket to connect to the server
			requestSocket = new Socket("localhost", port);
			log.debug("Connected to localhost in port "+port);
			//2. get Input and Output streams
			//out = new ObjectOutputStream(requestSocket.getOutputStream());
			out = requestSocket.getOutputStream();
			//pw = new PrintWriter(out,true);
			out.flush();
			//pw.write(xmlRequest);
			//send xmlRequest
			sendMessage();
			//send Request end
			//sendMessage("<REQ_END>");
			//in = new ObjectInputStream(requestSocket.getInputStream());
			in = requestSocket.getInputStream();
			//3: Communicating with the server
			boolean startrecvd = false;
			do{
				try{
					//message = (String)in.readObject();
					readData(in);
					//System.out.println("RECVD:>" + message);
					if (message.contains("<RESP_END>")){
						xmlResponse = message.substring(0,message.indexOf("<RESP_END>"));
						responseReceived = true;
						stoprequest = true;//;./pswx
					}else {
						message = null;
					}
					System.out.println("RECVD:>" + message);
					break;
					/*if (startrecvd){
						xmlResponse = message;
						startrecvd = false;
					}
					
					if (message.equals("START")){
						startrecvd = true;
						sendMessage();
						message = "END";
						sendMessage(message);
						message = "";
						responseReceived = true;
					}*/
					
					
				}
				catch(IOException ioException){
					log.error("Error reading data");
					errormessage = ioException.getMessage();
					if (errormessage == null){
						errormessage = "Error reading data";
					}					
					responseReceived = true;
					break;
				}
			}while(!stoprequest);
		}
		catch(UnknownHostException unknownHost){			
			log.error("You are trying to connect to an unknown host!");
			errormessage = unknownHost.getMessage();
			if (errormessage == null){
				errormessage = "You are trying to connect to an unknown host!";
			}
			responseReceived = true;			
		}
		catch(IOException ioException){			
			log.error("IOException");
			ioException.printStackTrace();
			errormessage = ioException.getMessage();
			if (errormessage == null){
				errormessage = "IOException";
			}			
			responseReceived = true;
		}
		finally{
			//4: Closing connection
			try{
				if (in!=null){
					in.close();
				}
				if (out!=null){
					out.close();
				}
				if (requestSocket != null){
					requestSocket.close();
				}
				
			}
			catch(IOException ioException){
				ioException.printStackTrace();
				errormessage = ioException.getMessage();
				if (errormessage == null){
					errormessage = "IOException";
				}
				responseReceived = true;				
			}
		}
	}
	
	void sendMessage(String msg)throws IOException
	{
		
			out.write(msg.getBytes());
			out.flush();
			//System.out.println("client>" + msg);		
	}	
	
	void sendMessage() throws IOException
	{
		
			//File f = new File(requestFile);
			//byte[] data = FileReaderUtil.readFile(f);
			out.write(xmlRequest.getBytes());		
			out.write("<REQ_END>".getBytes());
			out.flush();
			//System.out.println("SENT:>" + new String(data));
		
	}
	
	public String getXmlResponse() {
		return xmlResponse;
	}
	
	public void setStoprequest(boolean stoprequest) {
		this.stoprequest = stoprequest;
	}
	
	public boolean isResponseReceived() {
		return responseReceived;
	}
	
	public String getErrormessage() {
		if (errormessage != null){
			return errormessage;
		} else {
			return "Error executing Command";
		}
	}
	
	public void setPort(int port) {
		this.port = port;
	}	
	
	public static void main(String args[])
	{
		Requester client = new Requester();
		client.xmlRequest = "<SERVO_Module><TIMESTAMP>1293186398769</TIMESTAMP>" +
				"<COMMAND><ID>COLDSTART</ID>"+
				"<DATA>40</DATA>" +
				"</COMMAND></SERVO_Module>";
		client.port = 5000;
		client.run();
	}
	
	public void readData(InputStream in) throws IOException {
		try {
			int datalen = in.available();
			System.out.println("data size=" + datalen);
			while (!message.contains("<RESP_END>")) { // read data terminate reading when <RESP_END> recvd
				char bytedata = (char) in.read();
				//System.out.print(bytedata);
				message = message + String.valueOf(bytedata);

			}			
		} catch (IOException e) {
			e.printStackTrace();
			throw e;
		}
	}
	
}
