import java.io.BufferedReader;
import java.io.StringReader;
//import junit

public class InterviewQuestion {
	
	/**
	 * This function takes a space separated string of words and
	 * reverses the word order. So if the input string is
	 * "foo bar baz" the function will return "baz bar foo".
	 * 
	 * @param input a space separated string of words
	 * @return a space separated string of words in reverse order from the input
	 */
	public String reverseWords(String input){
		// empty string
		if(input.length()==0)
			return "";
		
		// trim original sting without leading a trailing white space
		input = input.trim();
		
		// split the input string and the delimiter is white space.
		String[] words = input.split(" +");
		
		// we use a StringBuffer to store result.
		StringBuffer result = new StringBuffer();
		
		// generate result from split string.
		for(int i=0;i<words.length;i++){
			result.insert(0, " "+ words[i]);
		}
		
		// delete the first redundant space
		result.deleteCharAt(0);
		
		// return result
		return result.toString();
	}
}

