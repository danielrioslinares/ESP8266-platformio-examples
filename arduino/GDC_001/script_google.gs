


var spreadsheet_google_id = ''; // ADD YOUR ACTUAL spreadsheet ID
var row = [];

function doGet(e) {

	// Result
	if (e.parameter != 'undefined') {

		var sheet = SpreadsheetApp.openById(spreadsheet_google_id).getActiveSheet();
		row[0] = new Date(); // Date and time

		// For each parameter...
		for (var param in e.parameter) {

			var value = stripQuotes(e.parameter[param]);
			// ...add it to the new row
			switch (param) {
				case 'variableOne':
					row[1] = value;
					break;
				case 'variableTwo':
					row[2] = value;
					break;
				case 'variableThr':
					row[3] = value;
					break;
				case 'variableFou':
					row[4] = value;
					break;
				default:
			}
		}

		// Append a new row
		sheet.getRange( sheet.getLastRow() + 1 , 1, 1, row.length ).setValues([row]);
	}

	// Return
	return 'Done';

}

function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}
