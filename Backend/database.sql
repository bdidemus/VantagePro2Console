-- Davis Weather station remote database
-- Brett Didemus
-- Oct 21 2012

CREATE TABLE Station (
	stID SERIAL,
	stDesc varchar(25),
	CONSTRAINT pk_station_stid PRIMARY KEY(stID));
	
CREATE TABLE Station_Data (
	datID			SERIAL,
	datDate			timestamp DEFAULT NOW(),
	datOutsideTemp	decimal(4,2),
	datInsideTemp	decimal(4,2),
	datOutsideHum	int,
	datInsideHum	int,
	datBarPress		decimal(4,2),
	datWindDir		int,
	datWindSpeed	int,
	datRainAmount	decimal(5,2),
	datSoilMoisture	int,
	stID			int,
	CONSTRAINT pk_station_data_datid PRIMARY KEY(datID),
	CONSTRAINT fk_station_data_stid FOREIGN KEY(stID) REFERENCES Station(stID));
	
	
INSERT INTO Station VALUES(1, "Main");
	
	