package population;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

public class Chart {
	private final int WIDTH = 1280;
	private final int HEIGHT = 1000;
	private Stage stg;
	private VBox vb;
	private HBox hb;
	private Button btn_close;
	private Button btn_clear;
	private ComboBox<String> cb_ctry;
	private ComboBox<Integer> cb_yearfrom;
	private ComboBox<Integer> cb_yearto;
	private NumberAxis xaxis;
	private NumberAxis yaxis;
	private LineChart<Number, Number> lc;
	private ArrayList<XYChart.Series<Number, Number>> sr;
	private List<Country> countries;
	
	Chart(List<Country> countries) {
		this.countries = countries;
		stg = mkstage();
		xaxis = mkxaxis("Year");
		yaxis = mkyaxis("Population");
		sr = new ArrayList<XYChart.Series<Number, Number>>();
		lc = mklinechart(xaxis, yaxis, stg);
		btn_close = mkclosebtn(stg, "Close");
		btn_clear = mkclearbtn(stg, sr, lc, "Clear");
		cb_ctry = mkctrylist(sr, lc, "Country");
		cb_yearfrom = mkyearcb(Country.STARTING_YEAR);
		cb_yearto = mkyearcb(Country.LAST_YEAR);
		
		/* Change timeline values. */
		cb_yearfrom.setOnAction(ev -> {
			if (cb_yearfrom.getValue() < cb_yearto.getValue())
				xaxis.setLowerBound(cb_yearfrom.getValue());
		});
		cb_yearto.setOnAction(ev -> {
			if (cb_yearto.getValue() > cb_yearfrom.getValue())
				xaxis.setUpperBound(cb_yearto.getValue());
		});
	}
	
	private Stage mkstage() {
		Stage stg = new Stage();
		
		stg.setWidth(WIDTH);
		stg.setHeight(HEIGHT);
		stg.initStyle(StageStyle.UTILITY);
		stg.initModality(Modality.WINDOW_MODAL);
		return stg;
	}
	
	private NumberAxis mkxaxis(String str) {
		NumberAxis xaxis = new NumberAxis();
		
		xaxis.setLabel(str);
		/* 
		 * By default, the chart isn't resized properly
		 * so we'll do it ourselves.
		 */
		xaxis.setLowerBound(Country.STARTING_YEAR);
		xaxis.setUpperBound(Country.LAST_YEAR);
		/* No. Stop auto resizing. */
		xaxis.setAutoRanging(false);
		return xaxis;
	}
	
	private NumberAxis mkyaxis(String str) {
		NumberAxis yaxis = new NumberAxis();
		
		yaxis.setLabel(str);
		return yaxis;
	}
	
	private XYChart.Series<Number, Number> mkseries(String str) {
		XYChart.Series<Number, Number> sr;
		
		sr = new XYChart.Series<Number, Number>();
		sr.setName(str);
		return sr;
	}
	
	private LineChart<Number, Number> mklinechart(
	    NumberAxis xaxis,
	    NumberAxis yaxis,
	    Stage stg) {
		LineChart<Number, Number> lc;
		
		lc = new LineChart<Number, Number>(xaxis, yaxis);
		
		/* Fit to screen. */
		lc.prefWidthProperty().bind(stg.widthProperty());
		lc.prefHeightProperty().bind(stg.heightProperty());
		
		/* 
		 * The animations look stupid when there's already another
		 * chart present.
		 */
		lc.setAnimated(false);
		
		/* Do not draw nodes, just the line. */
		lc.setCreateSymbols(false);
		
		return lc;
	}
	
	private Button mkclosebtn(Stage stg, String str) {
		Button btn_close = new Button(str);
		
		btn_close.setOnAction(ev -> {
			stg.close();
		});
		return btn_close;
	}

	private Button mkclearbtn(
	    Stage stg,
	    ArrayList<XYChart.Series<Number, Number>> sr,
	    LineChart<Number, Number> lc,
	    String str) {
		Button btn_clear = new Button(str);
		
		btn_clear.setOnAction(ev -> {
			lc.getData().clear();
			sr.forEach(s -> s.getData().clear());
			sr.clear();
		});
		return btn_clear;
	}
	
	private ComboBox<Integer> mkyearcb(Integer n) {
		ComboBox<Integer> cb = new ComboBox<Integer>();
		
		for (int i = Country.STARTING_YEAR; i <= Country.LAST_YEAR; i++)
			cb.getItems().add(i);
		/* 
		 * Set default values from the beginning, otherwise the 
		 * very first action will not work properly as the value
		 * in one of the ComboBoxes will be empty.
		 */
		cb.setValue(n);
		return cb;
	}
	
	private ComboBox<String> mkctrylist(
	    ArrayList<XYChart.Series<Number, Number>> sr,
	    LineChart<Number, Number> lc,
	    String str) {
		ComboBox<String> cb_ctry = new ComboBox<String>();
		
		countries.forEach(c -> cb_ctry.getItems().add(c.getName()));
		cb_ctry.setPromptText(str);
		/* 
		 * Sort countries by name, since by default
		 * each country is sorted by its index.
		 */
		Collections.sort(cb_ctry.getItems());
		
		/* Add population data for selected country to the chart. */
		cb_ctry.setOnAction(ev -> {
			Country c = null;
			Iterator<Map.Entry<Integer, Integer>> it;
			Map.Entry<Integer, Integer> ent;
			String ctryname;
			
			/* Search country by selection name. */
			ctryname = cb_ctry.getValue();
			for (Country ctry : countries) {
				if (ctry.getName().equals(ctryname)) {
					c = ctry;
					break;
				}
			}
			/* Possibly a useless check. */
			if (c == null)
				return;
			
			sr.add(mkseries(c.getName()));
			/* 
			 * Iterate through the population data and make
			 * the chart.
			 */
			it = c.getPopulation().entrySet().iterator();
			while (it.hasNext()) {
				ent = it.next();
				sr.get(sr.size()-1).getData().add(
				    new XYChart.Data<Number, Number>(
				        ent.getKey(), ent.getValue()));
			}
			lc.getData().add(sr.get(sr.size()-1));
		});
		return cb_ctry;
	}
	
	public void show() {
		/* Create bottom panel. */
		hb = new HBox();
		hb.setSpacing(5);
		hb.setAlignment(Pos.CENTER);
		hb.getChildren().addAll(cb_yearfrom, cb_yearto,
		    cb_ctry, btn_clear, btn_close);
		/* 
		 * Combine the chart and bottom panel, and display 
		 * the scene. 
		 */
		vb = new VBox();
		vb.setSpacing(5);
		vb.setPadding(new Insets(10, 10, 10, 10));
		vb.getChildren().addAll(lc, hb);
		stg.setTitle("Population Chart");
		stg.setScene(new Scene(vb, 400, 200));
		stg.show();
	}
}
