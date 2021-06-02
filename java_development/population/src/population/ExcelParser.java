package population;

import java.io.*;
import java.util.Iterator;
import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.*;

public class ExcelParser {
	private XSSFWorkbook wb;
	private XSSFSheet ss;
	private XSSFRow row;
	
	ExcelParser(String path) throws Exception {
		FileInputStream fis;
		Iterator<Row> rit;
		Iterator<Cell> cit;
		Cell cell;
		
		try {
			fis = new FileInputStream(new File(path));
			wb = new XSSFWorkbook(fis);
			ss = wb.getSheetAt(0);
			rit = ss.iterator();
			
			while (rit.hasNext()) {
				row = (XSSFRow)rit.next();
				cit = row.cellIterator();
				while (cit.hasNext()) {
					cell = cit.next();
					switch (cell.getCellType()) {
					case NUMERIC:
						System.out.print(
						    cell.getNumericCellValue() +
						    "\t\t");
						break;
					case STRING:
						System.out.print(
						    cell.getStringCellValue() +
						    "\t\t");
						break;
					case BOOLEAN:
						System.out.print(
						    cell.getBooleanCellValue() +
						    "\t\t");
						break;
					case BLANK: /* FALLTHROUGH */
					case ERROR:
					case FORMULA:
					case _NONE:
					default:
						break;
					}
				}
				System.out.println();
			}
			fis.close();
		} catch (FileNotFoundException e) {
			throw new Exception(path + ": no such file");
		} catch (IOException e) {
			throw new Exception("io error");
		}
	}
}
