import java.io.*;
import java.util.ArrayList;
import java.nio.ByteBuffer;

public class LZ77 {

	private static int dictBufferSize = 16383;
	private static int lookBufferSize = 1024;

	private static StringBuffer dictBuffer;
	private static byte[] lookBuffer;

	private class Triple {
		public int offset;
		public int length;
		public char nextChar;

		public Triple(int offset, int length, char nextChar) {
			this.offset = offset;
			this.length = length;
			this.nextChar = nextChar;
		}

		public Triple(byte[] bytes) {
			ByteBuffer bb = null;

			byte[] oarr = new byte[2];
			oarr[0] = bytes[0];
			oarr[1] = bytes[1];

			bb = ByteBuffer.wrap(oarr);
			this.offset = (int)bb.getShort();

			byte[] larr = new byte[2];
			larr[0] = bytes[2];
			larr[1] = bytes[3];

			bb = ByteBuffer.wrap(larr);
			this.length = (int)bb.getShort();

			this.nextChar = (char) bytes[4];
		}

		public byte[] toByteArray() {
			byte[] out = new byte[5];
			//offset bytes (2)
			byte[] oarr = null;
			//length btes (2)
			byte[] larr = null;
			//nextChar byte (1)
			byte carr = (byte) this.nextChar;

			//put the offs
			et
			ByteBuffer bb = ByteBuffer.allocate(2);
			bb.putShort((short) this.offset);
			oarr = bb.array();

			//put the length
			bb = ByteBuffer.allocate(2);
			bb.putShort((short) this.length);
			larr = bb.array();

			out[0] = oarr[0];
			out[1] = oarr[1];
			out[2] = larr[0];
			out[3] = larr[1];
			out[4] = carr;

			return out;
		}
	}

	public LZ77() {
		dictBuffer = new StringBuffer(dictBufferSize);
		lookBuffer = new byte[lookBufferSize];
	}

	//adopted from http://www.cs.waikato.ac.nz/~robi/comp209-03b/examples17/LZ77T.java
	private void trimDictBuffer() {
	    if (dictBuffer.length() > dictBufferSize) {
	      dictBuffer = dictBuffer.delete(0,  dictBuffer.length() - dictBufferSize);
	    }
    }

    public void encode2(String inputPath) throws Exception {
    	File file = new File(inputPath);
		FileInputStream fis = new FileInputStream(file);

		int numRead; //keeps track of # of bytes read

		//load the next bytes into thelookupbuffer
		//read in the file one char at a time
		String match = "";
		int tIndex = 0; //temp index of the immediate match
		int mIndex = 0; //match index
		int read;
		char nextChar;
		String resultStr = "";
		ArrayList<Triple> result = new ArrayList<Triple>();

		//look in lookBuffer for a match
		while( (read = fis.read()) != -1) {
			//get next char
			nextChar = (char) read;

			//look in the dict buffer for a match
			tIndex = dictBuffer.indexOf(match + nextChar);

			//if we find a match
			if(tIndex != -1) {
				match += nextChar;
				mIndex = tIndex;
			}
			//if we didnt find another match
			else {
				//we know thats the longest match possible
				//the triple is a 3 byte output
				//1st byte is the pointer to the match in the dictionary
				//2nd byte is the length of the match
				//3rd byte is the next character
				Triple trip = new Triple(mIndex, match.length(), nextChar);
				String concat = match + nextChar;
				
				//write the match
				//write the match out
				result.add(trip);
				//add the match to the dictionary window
				dictBuffer.append(concat);
				//write the dict buffer for debugging
				//clear the current match
				match = "";
				//reset the index of the match
				mIndex = 0;

				trimDictBuffer();
			}
		}
		//output leftover matches
		if(mIndex != -1) {
			//use ! as the eof representation
			Triple trip = new Triple(mIndex, match.length(), ' ');
			result.add(trip);
		}

		FileOutputStream fos = new FileOutputStream(new File(inputPath + ".lz77"));
		for(Triple t : result) {
			byte[] out = t.toByteArray();
			fos.write(out);
		}
		fos.close();
    }

    public void decode2(String filePath) throws Exception {
    	FileInputStream fis = new FileInputStream(new File(filePath));

    	byte[] buffer = new byte[5];
    	ArrayList<Triple> coded = new ArrayList<Triple>();

    	while(fis.read(buffer) != -1) {
    		Triple trip = new Triple(buffer);
    		coded.add(trip);
    		// System.out.println("Offset: " + trip.offset + "Length: " + trip.length + "NextChat: " + trip.nextChar);
    	}

    	int offset = 0;
    	int length = 0;

    	String resultStr = "";

    	for(Triple t : coded) {
    		offset = (int)t.offset; // set the offset
			length = (int)t.length;
			// output substring from search buffer
			String output = dictBuffer.substring(offset, offset+length) + t.nextChar;
			System.out.print(output);
			dictBuffer.append(output);
			// Adjust search buffer size if necessary
			trimDictBuffer();
    	}
    }

	public static void main(String args[]) {
		LZ77 comp = new LZ77();
		if(args[0].equals("1")) {
			try {		
				long startTime = System.nanoTime();
				comp.encode2(args[1]);
				long stopTime = System.nanoTime();
				long duration = (stopTime - startTime); 

				double ms = duration*1.0 / 1000000;

				System.out.println("time (ms): " + ms);
			}
			catch(Exception e){
				//dont care
				e.printStackTrace();
			}
		}
		else {
			try {		
				comp.decode2(args[1]);
			}
			catch(Exception e){
				//dont care
				e.printStackTrace();
			}
		}
	}
}