
----------------------------------Placing Requester.java------------------------------------------
1. Replace the Requester.java file in location CMS/src/com/psl/iucaa/services 
2. Clean and Build the eclipse project (Refer User Manual For NCRA  Setup.docx)
3. Run the cms application



----------------------------------Running Queue.c------------------------------------------------

Instructions for Compiling and executing the code

1. Compile the code as  > gcc  Queue.c  -lpthread
2. Run as   >./a.out
      Output:
	TCPServer Waiting for client on port 5000
3. Run a your client program  Which establishes connection on port 5000. - (Requester.java)

	OR Run sample client program provided 
                	Compile the code as > gcc client_NEW.c
	Run as   >./a.out

	Output: 

	Enter Data:  “ Write data here Manually”  press ‘ENTER’
	Enter Data:  <REQ_END>  press ‘ENTER’

4. Server waits till it receives <REQ_END>

5. After each client connection  Queue code creates  new thread for its data processing and is always ready for new connection.
     In a thread the processing of data is don so after success client data  it is put in to the Queue and Response is sent.

6. Consumer is a thread which extracts data from queue for further processing.

-------------------------------------Note---------------------------------------------------------------------------

The command and response formats specified in the code are reference only. 
The final command and response formats will evolve as the project progresses