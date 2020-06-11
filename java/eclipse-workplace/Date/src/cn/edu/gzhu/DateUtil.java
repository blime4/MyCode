package cn.edu.gzhu;

/**
 * This is a utility for Date
 * 
 * @author Liya
 * 
 */
public class DateUtil {
	public DateUtil() {
	}

	/**
	 * @param year
	 * @return true if year % 4 == 0 and year % 100 != 0 true if year % 100 == 0
	 *         and year % 400 == 0 false otherwise
	 */
	public static boolean isLeapYear(int year) {
		if (year % 4 == 0 && year % 100 != 0)
			return true;
		if (year % 100 == 0 && year % 400 != 0)
			return false;
		if (year % 100 == 0 && year % 400 == 0)
			return true;
		return false;
	}

	/**
	 * 
	 * @param date
	 * @return day of year，改日期是一年中的第几天
	 */
	public static int getDayofYear(Date date) {
		int sum = 0;
		if (isLeapYear(date.getYear())) {
			switch (date.getMonth()) {
			case 1:
				sum = 0;
				break;
			case 2:
				sum = 31;
				break;
			case 3:
				sum = 60;
				break;
			case 4:
				sum = 91;
				break;
			case 5:
				sum = 121;
				break;
			case 6:
				sum = 152;
				break;
			case 7:
				sum = 182;
				break;
			case 8:
				sum = 213;
				break;
			case 9:
				sum = 244;
				break;
			case 10:
				sum = 274;
				break;
			case 11:
				sum = 305;
				break;
			case 12:
				sum = 335;
				break;
			default:
				System.out.print("data error");
				break;

			}
		} else {
			switch (date.getMonth()) {
			case 1:
				sum = 0;
				break;
			case 2:
				sum = 31;
				break;
			case 3:
				sum = 59;
				break;
			case 4:
				sum = 90;
				break;
			case 5:
				sum = 120;
				break;
			case 6:
				sum = 151;
				break;
			case 7:
				sum = 181;
				break;
			case 8:
				sum = 212;
				break;
			case 9:
				sum = 243;
				break;
			case 10:
				sum = 273;
				break;
			case 11:
				sum = 304;
				break;
			case 12:
				sum = 334;
				break;
			default:
				System.out.print("data error");
				break;
			}
		}
		sum = sum + date.getDay(); 
		return sum;
	}
}
