import java.io.File;
import java.io.FileInputStream;

public class LZ77 {

	private static int dictBufferSize = 1024;
	private static int lookBufferSize = 1024;

	private static StringBuffer dictBuffer;
	private static byte[] lookBuffer;

	public LZ77() {
		dictBuffer = new StringBuffer(dictBufferSize);
		lookBuffer = new byte[lookBufferSize];
	}

	public void encode(String inputPath) throws Exception {
		File file = new File(inputPath);
		FileInputStream fis = new FileInputStream(file);

		int numRead; //keeps track of # of bytes read

		//load the next bytes into thelookupbuffer
		//read in the file one char at a time
		while((numRead = fis.read(lookBuffer)) != -1) {
			String match = "";
			int tIndex = 0; //temp index of the immediate match
			int mIndex = 0; //match index
			//look in dictBuffer for a match
			for(int i = 0; i < numRead; ++i) {
				//get the current char in the lookBuffer
				char currChar = (char) lookBuffer[i];
				//look in the dict buffer for a match
				tIndex = dictBuffer.indexOf(match + currChar);

				//if we find a match
				if(tIndex != -1) {
					match += currChar;
					mIndex = tIndex;
				}
				//if we didnt find another match
				else {
					//we know thats the longest match possible
					String coded;
				}
			}
		}

	}
	public void decode(String inputPath) {

	}

	public static void main(String args[]) {
		LZ77 comp = new LZ77();
		try {		
			comp.encode(args[0]);
		}
		catch(Exception e){
			//dont care
		}
	}
}