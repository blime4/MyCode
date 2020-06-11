package coolJUnit;


import static org.junit.Assert.*;
import org.junit.Test; 

public class SampleCalculatorTest {
	SampleCalculator calculator = new SampleCalculator(); 
	@Test
	public void testAdd() {
		int result = calculator.add(50, 20); 
		assertEquals(70,result); 
	}
	@Test  
	public void testSubtration() {
		int result = calculator.subtration(50, 20);
		assertEquals(30,result);
	}
}
