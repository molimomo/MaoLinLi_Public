import static org.junit.Assert.*;
import junit.framework.Assert;

import org.junit.Test;


public class InterviewQuestionTest {

	@Test
	public void testReverseWords() {
		InterviewQuestion interviewQuestion = new InterviewQuestion();
		
		// Given example test
		String actual = interviewQuestion.reverseWords("foo bar baz");
        Assert.assertEquals("baz bar foo", actual);
        
        // Empty string test
        actual = interviewQuestion.reverseWords("");
        Assert.assertEquals("", actual);
        
        // Single space
        actual = interviewQuestion.reverseWords(" ");
        Assert.assertEquals("", actual);
        
        // Single word test
        actual = interviewQuestion.reverseWords("word");
        Assert.assertEquals("word", actual);
        
        // Single character test
        actual = interviewQuestion.reverseWords("a");
        Assert.assertEquals("a", actual);
        
        // String consists of multiple characters 
        actual = interviewQuestion.reverseWords("a b c d");
        Assert.assertEquals("d c b a", actual);
        
        // String contains internal consecutive spaces
        actual = interviewQuestion.reverseWords("I am  a    programmer.");
        Assert.assertEquals("programmer. a am I", actual);
        
        // String contains leading and tailing spaces
        actual = interviewQuestion.reverseWords("    I am a programmer.    ");
        Assert.assertEquals("programmer. a am I", actual);
	}

}
