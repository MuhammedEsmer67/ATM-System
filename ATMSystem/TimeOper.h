#pragma once
#pragma warning (disable : 4996)
#include <iostream>
#include <ctime>

using namespace std;
namespace Time

{
	enum enCompareDates { Before = -1, Equal = 0, After = 1 };

	struct stDate
	{
		short Day;
		short Month;
		short Year;
	};

	struct stPeriod
	{
		stDate StartDateInfo;
		stDate EndDateInfo;
	};

	bool fnCheckIfLeapYear(short Year)
	{
		return (Year % 400 == 0) || (Year % 100 != 0 && Year % 4 == 0);
	}

	short fnDaysInYear(bool isLeapYear)
	{
		return (isLeapYear) ? 366 : 365;
	}

	short fnHoursInYear(short DaysInYear)
	{
		return 24 * DaysInYear;
	}

	int fnMinutesInYear(short HoursInYear)
	{
		return 60 * HoursInYear;
	}

	int fnSecondsInYear(int MinutesInYear)
	{
		return 60 * MinutesInYear;
	}

	short fnDaysInMonth(short Month, short Year)
	{
		int MonthsDaysArray[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? (fnCheckIfLeapYear(Year) ? 29 : 28) : MonthsDaysArray[Month];
	}

	short fnHoursInMonth(short Month, short Year)
	{
		return 24 * fnDaysInMonth(Month, Year);
	}

	int fnMinutesInMonth(short Month, short Year)
	{
		return 60 * fnHoursInMonth(Month, Year);
	}

	int fnSecondsInMonth(short Month, short Year)
	{
		return 60 * fnMinutesInMonth(Month, Year);
	}

	bool fnCheckIfDayInvalid(short Year, short Month, short Day)
	{
		return (Day > fnDaysInMonth(Month, Year));
	}

	short fnCalculateDayIndex(short Year, short Month, short Day)
	{
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + 12 * a - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	string fnPrintDays(short DayIndex)
	{
		string DaysArray[7] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };

		return DaysArray[DayIndex];
	}

	string fnPrintMonths(short Month)
	{
		string MonthsArray[13] = { "","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

		return MonthsArray[Month];
	}

	void prPrintCalenderInterface(short Year, short Month)
	{
		short DaysInMonth = fnDaysInMonth(Month, Year);
		short DayIndex = fnCalculateDayIndex(Year, Month, 1);

		cout << "\n ________________" << fnPrintMonths(Month) << "________________\n\n";
		cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

		for (short i = 1; i <= DayIndex; i++)
			cout << "     ";

		for (short j = 1; j <= DaysInMonth; j++)
		{
			printf("%5d", j);

			if (++DayIndex == 7)
			{
				DayIndex = 0;
				cout << endl;
			}
		}

		cout << "\n ____________________________________\n";
	}

	short fnCalculateTotalDaysToDate(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (short i = 1; i < Month; i++)
			TotalDays += fnDaysInMonth(i, Year);

		TotalDays += Day;

		return TotalDays;
	}

	stDate fnConvertDayOrderToDate(short Year, short DayOrder)
	{
		stDate DateInfo;
		DateInfo.Month = 0;
		DateInfo.Year = Year;

		while (DayOrder > 0)
			DayOrder -= fnDaysInMonth(++DateInfo.Month, Year);

		DayOrder += fnDaysInMonth(DateInfo.Month, Year);
		DateInfo.Day = DayOrder;

		return DateInfo;
	}

	stDate fnAddDaysToDate(short Year, short Month, short Day, short DaysToAdd)
	{
		stDate DateInfo;
		DateInfo.Month = Month - 1;
		DateInfo.Year = Year;
		DaysToAdd += Day;

		while (DaysToAdd > 0)
		{
			if (++DateInfo.Month > 12)
			{
				DateInfo.Month = 1;
				DateInfo.Year++;
			}

			DaysToAdd -= fnDaysInMonth(DateInfo.Month, DateInfo.Year);
		}

		DaysToAdd += fnDaysInMonth(DateInfo.Month, DateInfo.Year);
		DateInfo.Day = DaysToAdd;

		return DateInfo;
	}

	bool fnisDate1AfterDate2(stDate StartDateInfo, stDate EndDateInfo)
	{
		return (StartDateInfo.Year > EndDateInfo.Year ? true : (StartDateInfo.Year == EndDateInfo.Year ? (StartDateInfo.Month > EndDateInfo.Month ? true : (StartDateInfo.Month == EndDateInfo.Month ? (StartDateInfo.Day > EndDateInfo.Day) : false)) : false));
	}

	bool fnareDatesEqual(stDate StartDateInfo, stDate EndDateInfo)
	{
		return (StartDateInfo.Year == EndDateInfo.Year && StartDateInfo.Month == EndDateInfo.Month && StartDateInfo.Day == EndDateInfo.Day);
	}

	bool fnCheckIfLastDayInMonth(short Day, short Month, short Year)
	{
		return (fnDaysInMonth(Month, Year) == Day);
	}

	bool fnCheckIfLastMonth(short Month)
	{
		return (Month == 12);
	}

	stDate fnIncreaseDateOneDay(stDate DateInfo)
	{
		fnCheckIfLastDayInMonth(DateInfo.Day, DateInfo.Month, DateInfo.Year) ? (DateInfo.Day = 1, (fnCheckIfLastMonth(DateInfo.Month)) ? DateInfo.Month = 1, DateInfo.Year++ : DateInfo.Month++) : DateInfo.Day++;

		return DateInfo;
	}

	bool fnisDate1BeforeDate2(stDate StartDateInfo, stDate EndDateInfo)
	{
		return !(fnisDate1AfterDate2(StartDateInfo, EndDateInfo) || fnareDatesEqual(StartDateInfo, EndDateInfo));
	}

	short fnDate1Date2Difference(stDate StartDateInfo, stDate EndDateInfo, bool isIncludeLastDay = false)
	{
		short SwapFlagValue = 1;
		short DaysDiffCounter = 0;
		stDate Temp;

		if (fnisDate1AfterDate2(StartDateInfo, EndDateInfo))
		{
			Temp = StartDateInfo;
			StartDateInfo = EndDateInfo;
			EndDateInfo = Temp;

			SwapFlagValue = -1;
		}

		while (!fnareDatesEqual(StartDateInfo, EndDateInfo))
		{
			DaysDiffCounter++;
			StartDateInfo = fnIncreaseDateOneDay(StartDateInfo);
		}

		return isIncludeLastDay ? ++DaysDiffCounter * SwapFlagValue : DaysDiffCounter * SwapFlagValue;
	}

	stDate fnGetSystemDate()
	{
		stDate DateInfo;

		time_t TimeInSec = time(0);
		tm* stTime = localtime(&TimeInSec);

		DateInfo.Day = stTime->tm_mday;
		DateInfo.Month = stTime->tm_mon + 1;
		DateInfo.Year = stTime->tm_year + 1900;

		return DateInfo;
	}

	stDate fnIncreaseDateXDays(stDate DateInfo, short XDays)
	{
		for (short i = 1; i <= XDays; i++)
			DateInfo = fnIncreaseDateOneDay(DateInfo);
	
		return DateInfo;
	}

	stDate fnIncreaseDateOneMonth(stDate DateInfo)
	{
		fnCheckIfLastMonth(DateInfo.Month) ? DateInfo.Month = 1, DateInfo.Year++ : DateInfo.Month++;

		short NewMonthDays = fnDaysInMonth(DateInfo.Month, DateInfo.Year);

		if (DateInfo.Day > NewMonthDays)
			DateInfo.Day = NewMonthDays;

		return DateInfo;
	}

	stDate fnIncreaseDateXMonths(stDate DateInfo, short XMonths)
	{
		for (short i = 1; i <= XMonths; i++)
			DateInfo = fnIncreaseDateOneMonth(DateInfo);

		return DateInfo;
	}

	stDate fnIncreaseDateXYearsFaster(stDate DateInfo, short XYears)
	{
		DateInfo.Year += XYears;

		if (!(fnCheckIfLeapYear(DateInfo.Year)) && DateInfo.Month == 2 && DateInfo.Day == 29)
		{
			DateInfo.Day = 1;
			DateInfo.Month = 3;
		}

		return DateInfo;
	}

	bool fnCheckIfFirstMonth(short Month)
	{
		return (Month == 1);
	}

	bool fnCheckIfFirstDay(short Day)
	{
		return (Day == 1);
	}

	stDate fnDecreaseDateOneDay(stDate DateInfo)
	{
		fnCheckIfFirstDay(DateInfo.Day) ? (fnCheckIfFirstMonth(DateInfo.Month) ? DateInfo.Year--, DateInfo.Month = 12, DateInfo.Day = 31 : DateInfo.Month--, DateInfo.Day = fnDaysInMonth(DateInfo.Month, DateInfo.Year)) : DateInfo.Day--;

		return DateInfo;
	}

	stDate fnDecreaseDateXDays(stDate DateInfo, short XDays)
	{
		for (short i = 1; i <= XDays; i++)
			DateInfo = fnDecreaseDateOneDay(DateInfo);

		return DateInfo;
	}

	stDate fnDecreaseDateOneMonth(stDate DateInfo)
	{
		fnCheckIfFirstMonth(DateInfo.Month) ? DateInfo.Month = 12, DateInfo.Year-- : DateInfo.Month--;

		short NewMonthDays = fnDaysInMonth(DateInfo.Month, DateInfo.Year);

		if (DateInfo.Day > NewMonthDays)
			DateInfo.Day = NewMonthDays;

		return DateInfo;
	}

	stDate fnDecreaseDateXMonths(stDate DateInfo, short XMonths)
	{
		for (short i = 1; i <= XMonths; i++)
			DateInfo = fnDecreaseDateOneMonth(DateInfo);

		return DateInfo;
	}

	stDate fnDecreaseDateXYearsFaster(stDate DateInfo, short XYears)
	{
		DateInfo.Year -= XYears;

		if (!(fnCheckIfLeapYear(DateInfo.Year)) && DateInfo.Month == 2 && DateInfo.Day == 29)
			DateInfo.Day = 28;

		return DateInfo;
	}

	bool fnisEndOfWeek(stDate DateInfo)
	{
		short DayIndex = fnCalculateDayIndex(DateInfo.Year, DateInfo.Month, DateInfo.Day);

		return (DayIndex == 6);
	}

	bool fnisWeekEnd(stDate DateInfo)
	{
		short DayIndex = fnCalculateDayIndex(DateInfo.Year, DateInfo.Month, DateInfo.Day);

		return (DayIndex == 0 || DayIndex == 6);
	}

	bool fnisBusinessDay(stDate DateInfo)
	{
		return !fnisWeekEnd(DateInfo);
	}

	short fnDaysUntilEndOfWeek(short DayIndex)
	{
		return 6 - DayIndex;
	}

	short fnDaysUntilEndOfMonth(stDate DateInfo)
	{
		return fnDaysInMonth(DateInfo.Month, DateInfo.Year) - DateInfo.Day;
	}

	short fnDaysUntilEndOfYear(stDate DateInfo)
	{
		return fnDaysInYear(fnCheckIfLeapYear(DateInfo.Year)) - fnCalculateTotalDaysToDate(DateInfo.Day, DateInfo.Month, DateInfo.Year);
	}

	short fnCalculateVacationDays(stDate StartDateInfo, stDate EndDateInfo)
	{
		short DaysDiffCounter = 0;

		while (!fnareDatesEqual(StartDateInfo, EndDateInfo))
		{
			if (fnisBusinessDay(StartDateInfo))
				DaysDiffCounter++;

			StartDateInfo = fnIncreaseDateOneDay(StartDateInfo);
		}

		return DaysDiffCounter;
	}

	stDate fnCalculateVacationReturnDay(stDate DateInfo, short VacationDays)
	{
		while (VacationDays > 0)
		{
			if (fnisBusinessDay(DateInfo))
				VacationDays--;

			DateInfo = fnIncreaseDateOneDay(DateInfo);
		}

		while (Time::fnisWeekEnd(DateInfo))
			DateInfo = fnIncreaseDateOneDay(DateInfo);

		return DateInfo;
	}

	enCompareDates fnCompareDateFunctions(stDate StartDateInfo, stDate EndDateInfo)
	{
		return (fnareDatesEqual(StartDateInfo, EndDateInfo) ? enCompareDates::Equal : (fnisDate1AfterDate2(StartDateInfo, EndDateInfo) ? enCompareDates::After : enCompareDates::Before));
	}

	bool fnCheckIfPeriodsOverlap(stPeriod Period1, stPeriod Period2)
	{
		return !(fnCompareDateFunctions(Period2.StartDateInfo, Period1.EndDateInfo) == enCompareDates::After || fnisDate1AfterDate2(Period1.StartDateInfo, Period2.EndDateInfo));
	}

	bool fnCheckIfDateWithinPeriod(stPeriod Period, stDate DateToCheck)
	{
		return !(fnCompareDateFunctions(DateToCheck, Period.StartDateInfo) == enCompareDates::Before || fnCompareDateFunctions(Period.EndDateInfo, DateToCheck) == enCompareDates::After);
	}

	short fnCalculateOverlapDays(Time::stPeriod Period1, Time::stPeriod Period2)
	{
		int overlap_days = 0;
		Time::stDate start_edge;
		Time::stDate end_edge;

		if (!Time::fnCheckIfPeriodsOverlap(Period1, Period2))
			return overlap_days;

		start_edge = (Time::fnCompareDateFunctions(Period1.StartDateInfo, Period2.StartDateInfo) == Time::enCompareDates::Before) ? Period2.StartDateInfo : Period1.StartDateInfo;
		end_edge = (Time::fnCompareDateFunctions(Period1.EndDateInfo, Period2.EndDateInfo) == Time::enCompareDates::After) ? Period2.EndDateInfo : Period1.EndDateInfo;

		overlap_days = Time::fnDate1Date2Difference(start_edge, end_edge, true);

		return overlap_days;
	}

	bool fnisValidDate(stDate DateInfo)
	{
		return (Time::fnDaysInMonth(DateInfo.Month, DateInfo.Year) < DateInfo.Day) ? false : ((12 < DateInfo.Month) ? false : true);
	}

}