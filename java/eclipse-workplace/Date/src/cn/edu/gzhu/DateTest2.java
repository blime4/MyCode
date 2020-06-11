package cn.edu.gzhu;

import static org.junit.Assert.*;

import org.junit.Test;

import java.time.LocalDateTime;


public class DateTest2 {
	private Date date;

	public void setup() throws Exception{
		this.date = new Date();
	}

	
	@Test
	public void testIsDayValid() {
		//2000�������꣬�����꣬����1������
		assertTrue(this.date.isDayValid(2000, 1, 3));
		assertTrue(this.date.isDayValid(2000, 1, 0));
		assertTrue(this.date.isDayValid(2000, 1, 1));
		assertTrue(this.date.isDayValid(2000, 1, 31));
		assertTrue(this.date.isDayValid(2000, 1, 32));
		assertTrue(this.date.isDayValid(2000, 1, 30));
		assertTrue(this.date.isDayValid(2000, 1, -1));
		//2000�������꣬�����꣬����2������
		assertTrue(this.date.isDayValid(2000, 2, 9));
		assertTrue(this.date.isDayValid(2000, 2, 0));
		assertTrue(this.date.isDayValid(2000, 2, 1));
		assertTrue(this.date.isDayValid(2000, 2, 31));
		assertTrue(this.date.isDayValid(2000, 2, 30));
		assertTrue(this.date.isDayValid(2000, 2, 29));
		assertTrue(this.date.isDayValid(2000, 2, 28));
		assertTrue(this.date.isDayValid(2000, 2, -1));
		//2003��ƽ�꣬����9������
		assertTrue(this.date.isDayValid(2000, 4, 9));
		assertTrue(this.date.isDayValid(2000, 4, 0));
		assertTrue(this.date.isDayValid(2000, 4, 1));
		assertTrue(this.date.isDayValid(2000, 4, 31));
		assertTrue(this.date.isDayValid(2000, 4, 30));
		assertTrue(this.date.isDayValid(2000, 4, -1));
		//2003��ƽ�꣬����2������
		assertTrue(this.date.isDayValid(2000, 2, 9));
		assertTrue(this.date.isDayValid(2000, 2, 0));
		assertTrue(this.date.isDayValid(2000, 2, 1));
		assertTrue(this.date.isDayValid(2000, 2, 31));
		assertTrue(this.date.isDayValid(2000, 2, 30));
		assertTrue(this.date.isDayValid(2000, 2, 29));
		assertTrue(this.date.isDayValid(2000, 2, -1));
		//2004�����꣬����2������
		assertTrue(this.date.isDayValid(2000, 2, 9));
		assertTrue(this.date.isDayValid(2000, 2, 0));
		assertTrue(this.date.isDayValid(2000, 2, 1));
		assertTrue(this.date.isDayValid(2000, 2, 31));
		assertTrue(this.date.isDayValid(2000, 2, 30));
		assertTrue(this.date.isDayValid(2000, 2, 29));
		assertTrue(this.date.isDayValid(2000, 2, 28));
		assertTrue(this.date.isDayValid(2000, 2, -1));
	}
	
	@Test
	public void testIsMonthValid() {
		assertTrue(this.date.isMonthValid(-1));
		assertFalse(this.date.isMonthValid(0));
		assertFalse(this.date.isMonthValid(13));
		assertTrue(this.date.isMonthValid(1));
		assertTrue(this.date.isMonthValid(12));
		assertTrue(this.date.isMonthValid(7));
	}
	@Test
	public void testIsYearValid() {
		assertTrue(this.date.isYearValid(1));
		assertFalse(this.date.isYearValid(-1));
		assertFalse(this.date.isYearValid(0));
		assertFalse(this.date.isYearValid(2020));
	}
	@Test
	public void testIsLeapYear() {
		assertFalse(DateUtil.isLeapYear(200)); //�ܱ�4��100����
		assertTrue(DateUtil.isLeapYear(8)); //�ܱ�4����
		assertFalse(DateUtil.isLeapYear(600));//�ܱ�4��100���������ܱ�400����
		assertTrue(DateUtil.isLeapYear(2000));//�ܱ�4��100�������ܱ�400����
		assertFalse(DateUtil.isLeapYear(-1));//����
		assertFalse(DateUtil.isLeapYear(0));//0
		assertFalse(DateUtil.isLeapYear(1));
	}
	@Test
	public void testGetDayofYear() {
		int ans = 0;
		Date Date1=new Date(2020,4,16);
		int solution1=DateUtil.getDayofYear(Date1);
		assertEquals(107,solution1);
		Date Date2=new Date(2020,11,23);
		int solution3=DateUtil.getDayofYear(Date2);
		assertEquals(328,solution3);
		Date Date3=new Date(2019,9,25);
		int solution4=DateUtil.getDayofYear(Date3);
		assertEquals(268,solution4);
	}

}


