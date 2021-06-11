package population;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableRow;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.FileChooser;
import javafx.stage.FileChooser.ExtensionFilter;
import javafx.stage.Stage;

public class MainWindow {
	private final int WIDTH = 1000;
	private final int HEIGHT = 900;
	private List<Country> countries;
	private TableView<Country> tbv;
	private HBox btns;
	private Stage stg;
	private String title;
	
	MainWindow(Stage stg, String title) {
		this.stg = stg;
		this.title = title;
	}

	public void setup(String path) {
		ExcelParser ep;
		
		try {
			ep = new ExcelParser(path);
			countries = ep.get_countries();
		} catch (FileNotFoundException e) {
			err(path + ": no such file");
			return;
		} catch (IndexOutOfBoundsException e) {
			err("usage: population xlsx_file");
			return;
		} catch (IOException e) {
			err(path + ": io error");
			return;
		} catch (Exception e) {
			err(e.getMessage());
			return;
		}
		mktable();
		mkbtns();
		stg.setTitle(title + " - " + path);
		stg.setWidth(WIDTH);
		stg.setHeight(HEIGHT);
	}
	
	public void show() {
		stg.setScene(new Scene(mkvbox(tbv, btns)));
		stg.show();
	}
	
	private void err(String errstr) {
		Alert alert;
		
		alert = new Alert(AlertType.ERROR, errstr, ButtonType.CLOSE);
		alert.showAndWait();
	}
	
	private void mkbtns() {
		ComboBox<String> cb;
		Button btn_file;
		Button btn_chart;
		Button btn_exit;

		btn_file = new Button("Load File");
		btn_file.setOnAction(ev -> {
			FileChooser fc = new FileChooser();
			fc.setTitle("Load File");
			fc.getExtensionFilters().add(
			    new ExtensionFilter("XLSX Files", "*.xlsx"));
			setup(fc.showOpenDialog(stg).getAbsolutePath());
		});
		
		btn_chart = new Button("Chart");
		btn_chart.setOnAction(ev -> {
			Chart chart = new Chart(countries);
			chart.show();
		});
		
		btn_exit = new Button("Exit");
		btn_exit.setOnAction(ev -> {
			Platform.exit();
			System.exit(0);
		});
		
		cb = new ComboBox<String>();
		for (int i = Country.STARTING_YEAR; i <= Country.LAST_YEAR; i++)
			cb.getItems().add(String.valueOf(i));
		cb.setPromptText("Year");
		cb.setOnAction(ev -> {
			for (Country ctry : countries) {
				ctry.setCurpop(Integer.valueOf(cb.getValue()));
				tbv.refresh();
			}
		});
		
		btns = new HBox();
		btns.getChildren().addAll(btn_file, cb, btn_chart, btn_exit);
		btns.setSpacing(5);
		btns.setAlignment(Pos.CENTER);
	}
	
	private void mktable() {
		TableColumn<Country, String> tbc;
		List<Column> cols;
		ObservableList<Country> addrs;
		
		cols = new ArrayList<Column>(Arrays.asList(
		    new Column("Index", "index"),
		    new Column("Variant", "variant"),
		    new Column("Country", "name"),
		    new Column("Notes", "notes"),
		    new Column("Country Code", "ctrycode"),
		    new Column("Type", "type"),
		    new Column("Parent Code", "pntcode"),
		    new Column("Population", "curpop")
		));
		tbv = new TableView<Country>();
		addrs = FXCollections.observableArrayList(countries);
		for (Column col : cols) {
			tbc = new TableColumn<Country, String>(col.get_name());
			/* Why is this line so long? */
			tbc.setCellValueFactory(
			    new PropertyValueFactory<Country, String>(
			        col.get_fieldname()));
			tbv.getColumns().add(tbc);
		}
		tbv.setRowFactory(tv -> {
			TableRow<Country> row = new TableRow<Country>();
			row.setOnMouseClicked(ev -> {
				if (ev.getClickCount() == 2 && !row.isEmpty()) {
					Country c = row.getItem();
					Toast toast = new Toast(c, stg);
					toast.show();
				}
			});
			return row;
		});
		tbv.setItems(addrs);
		/* Fit to screen. */
		tbv.prefWidthProperty().bind(stg.widthProperty());
		tbv.prefHeightProperty().bind(stg.heightProperty());
	}
	
	private VBox mkvbox(TableView<Country> tbv, HBox btns) {
		VBox vb = new VBox();
		
		vb.setSpacing(5);
		vb.setPadding(new Insets(10, 10, 10, 10));
		vb.getChildren().addAll(tbv, btns);
		return vb;
	}
}
