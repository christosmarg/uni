package population;

import java.io.File;
import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Iterator;
import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.*;

public class ExcelParser {
	private final String EST_SHEET = "ESTIMATES";
	private final String TARGET_TYPE = "Country/Area";
	private final int TARGET_TYPE_CELL = 5;
	private final int HEADER_ROW = 16;
	private final int COUNTRIES_ROW = 44;
	private ArrayList<Country> countries;
	private XSSFRow row;
	
	ExcelParser(String path) throws Exception {
		XSSFWorkbook wbook;
		XSSFSheet sheet;
		FileInputStream fis;
		Iterator<Row> rit;
		String cv = "";
		int rownum;

		countries = new ArrayList<Country>();
		fis = new FileInputStream(new File(path));
		wbook = new XSSFWorkbook(fis);
		sheet = wbook.getSheet(EST_SHEET);
		rit = sheet.iterator();

		while (rit.hasNext()) {
			row = (XSSFRow)rit.next();
			rownum = row.getRowNum();
			cv = row.getCell(TARGET_TYPE_CELL).getStringCellValue();
			/* TODO: Separate header */
			if (rownum == HEADER_ROW
			|| (rownum>= COUNTRIES_ROW && cv.equals(TARGET_TYPE)))
				countries.add(read_country(row));
		}
		wbook.close();
		fis.close();
	}
	
	private Country read_country(XSSFRow row) throws Exception {
		Country ctry = new Country();
		Iterator<Cell> cit = row.cellIterator();
		Cell cell;
		String str = "";
		
		while (cit.hasNext()) {
			cell = cit.next();
			switch (cell.getCellType()) {
			case STRING:
				str = cell.getStringCellValue(); 
				break;
			case NUMERIC:
				str = String.valueOf(
				    cell.getNumericCellValue());
				break;
			case BOOLEAN:
				str = String.valueOf(
				    cell.getBooleanCellValue());
				break;
			case BLANK:
				str = "0";
			case ERROR: /* FALLTHROUGH */
			case FORMULA:
			case _NONE:
			default:
				break;
			}
			System.out.print(str + "\t\t");
		}
		System.out.println();
		
		return ctry;
	}
	
	public ArrayList<Country> get_countries() {
		return countries;
	}
}
