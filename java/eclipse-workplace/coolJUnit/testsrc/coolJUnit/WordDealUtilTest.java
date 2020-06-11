package coolJUnit;

import static org.junit.Assert.*;
import org.junit.Test;

public class WordDealUtilTest {

	@Test
	public void testWordFormat4DB() {
		String target = "employeeInfo";
		String result = WordDealUtil.wordFormat4DB(target);
		assertEquals("employee_info", result);
	}
	@Test 
	public void wordFormat4DBNull(){
		String target = null;
		String result = WordDealUtil.wordFormat4DB(target);
		assertNull(result);
	}
	@Test
	public void wordFormat4DBEmpty(){
		String target = "";
		String result = WordDealUtil.wordFormat4DB(target);
		assertEquals("", result);
	}
	@Test
	public void wordFormat4DBegin(){
		String target = "EmployeeInfo";
		String result = WordDealUtil.wordFormat4DB(target);
		assertEquals("employee_info", result);
	}
	@Test
	public void wordFormat4DBEnd(){
		String target = "employeeInfoA";
		String result = WordDealUtil.wordFormat4DB(target);
		assertEquals("employee_info_a", result);
	}
	@Test 
	public void wordFormat4DBTogether(){
		String target = "employeeAInfo";
		String result = WordDealUtil.wordFormat4DB(target);
		assertEquals("employee_a_info", result);
	} 
}
