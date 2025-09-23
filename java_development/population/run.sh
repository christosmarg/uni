#!/bin/sh

/usr/local/openjdk11/bin/java \
	--module-path /usr/local/openjfx14/lib \
	--add-modules javafx.controls,javafx.fxml \
	-jar population.jar \
	res/wpp2019_population_both_sexes.xlsx
