package cn.edu.gzhu;

/**
 * @author Liya
 *
 */
public class Date {
	public Date() {
	}

	public Date(int year, int month, int day) {
		super();
		if (this.isDayValid(year, month, day) && this.isMonthValid(month)
				&& this.isYearValid(year)) {
			this.year = year;
			this.month = month;
			this.day = day;
		}else{
			throw new IllegalArgumentException("Please check your input!");
		}
	}

	/**
	 * 0 < year
	 */
	private int year = -1;

	/**
	 * 1 <= month <= 12
	 */
	private int month = -1;

	/**
	 * 1 <= day <=31 the day should in the scope [1, 30] when the month is: 4,
	 * 6, ,9, 11 the day should in the scope [1, 31] when the month is: 1, 3, 5,
	 * 7, 8, 10, 12 the day should in the scope [1, 28] when the month is 2 and
	 * the year is not leap year @see the day should in the scope [1, 29] when
	 * the month is 2 and the year is leap year @see
	 */
	private int day = -1;

	public boolean isDayValid(int year, int month, int day) {
		if ((month == 4 || month == 6 || month == 9 || month == 11) && (day <= 30 && day >= 1)) return true;
		if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30 || day < 1)) return false;

		if ((month == 1 || month == 3 || month == 5 || month == 7|| month == 8 || month == 10 || month == 12) && (day <= 31 || day >= 1)) return true;
		if ((month == 1 || month == 3 || month == 5 || month == 7|| month == 8 || month == 10 || month == 12) && (day > 31 || day < 1)) return false;

		if(month == 2 && DateUtil.isLeapYear(year) && (day >= 1 || day <= 29)) return true;
		if(month == 2 && DateUtil.isLeapYear(year) && (day < 1 || day > 29)) return false;

		if(month == 2 && !DateUtil.isLeapYear(year) && (day >= 1 && day <= 28)) return true;
		if(month == 2 && !DateUtil.isLeapYear(year) && (day < 1 || day > 28)) return false;
		return false;
	}

	public boolean isMonthValid(int month) {
		return month >= 1 && month <= 12;
	}

	public boolean isYearValid(int year) {
		return year > 0;
	}

	public int getYear() {
		return year;
	}

	public void setYear(int year) {
		if (this.isYearValid(year)) {
			this.year = year;
		}else{
			throw new IllegalArgumentException("Please check your input!");
		}
	}

	public int getMonth() {
		return month;
	}

	public void setMonth(int month) {
		if (this.isMonthValid(month)) {
			this.month = month;
		}else{
			throw new IllegalArgumentException("Please check your input!");
		}
	}

	public int getDay() {
		return day;
	}

	public void setDay(int day) {
		if (this.year == -1 || this.month == -1) throw new IllegalStateException("You should set the year and month before day!");
		if (this.isDayValid(year, month, day)) {
			this.day = day;
		}else{
			throw new IllegalArgumentException("Please check your input!");
		}
	}

}
