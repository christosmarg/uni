package population;

import java.io.File;
import java.io.FileInputStream;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.*;

public class ExcelParser {
	private final String EST_SHEET = "ESTIMATES";
	private final String TARGET_TYPE = "Country/Area";
	private final int TARGET_TYPE_CELL = 5;
	private final int COUNTRIES_ROW = 43;
	private List<Country> countries;
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
			if (rownum>= COUNTRIES_ROW && cv.equals(TARGET_TYPE))
				countries.add(read_country(row));
		}
		wbook.close();
		fis.close();
	}
	
	private Country read_country(XSSFRow row) throws Exception {
		final int MIN_CELLNUM = 7;
		Country ctry;
		Iterator<Cell> cit;
		Cell cell;
		Integer year = Main.STARTING_YEAR;
		String[] fields = new String[MIN_CELLNUM];
		HashMap<Integer, Integer> population = new HashMap<Integer, Integer>();
		Integer n;
		int i = 0;

		cit = row.cellIterator();
		if (row.getLastCellNum() < MIN_CELLNUM) {
			throw new Exception("file must have at least " +
			    MIN_CELLNUM + " columns");
		}
		while (cit.hasNext()) {
			cell = cit.next();
			if (i < MIN_CELLNUM) {
				switch (cell.getCellType()) {
				case STRING:
					fields[i++] = cell.getStringCellValue(); 
					break;
				case NUMERIC:
					/* 
					 * We'll need another conversion back to
					 * Integer, but it's easier to do it that
					 * way than to keep lots of variables
					 * and hardcode everything.
					 */
					n = dtoi(cell.getNumericCellValue());
					fields[i++] = Integer.toString(n);
					break;
				case BOOLEAN:
					fields[i++] = String.valueOf(
					    cell.getBooleanCellValue());
					break;
				case BLANK:
					fields[i++] = "0";
					break;
				case ERROR: /* FALLTHROUGH */
				case FORMULA:
				case _NONE:
				default:
					fields[i++] = "";
					break;
				}
			} else if (cell.getCellType() == CellType.NUMERIC)
				/* 
				 * Population numbers need to be multiplied by
				 * 1000 in order to convert them properly to
				 * Integer.
				 */
				population.put(year++,
				    dtoi(cell.getNumericCellValue() * 1000));
		}
		ctry = new Country(fields[0], fields[1], fields[2], fields[3],
		    fields[4], fields[5], fields[6], population);

		return ctry;
	}
	
	private Integer dtoi(double n) {
		Double d;
		
		d = Double.valueOf(n);
		return Integer.valueOf(d.intValue());
	}
	
	public List<Country> get_countries() {
		return countries;
	}
}
