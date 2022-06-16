#if defined _dialog_inc
	#endinput
#endif
#define _dialog_inc

#include	<foreach>

enum E_DIALOGS {
	ed_ButtonL[32],
	ed_ButtonR[32],
	ed_Info[4096],
	ed_Title[64],
	ed_Name[32],
	ed_Style
}

new varDialog[2000][E_DIALOGS];
new Iterator:Dialog<2000>;

stock bool:IsValidDialog(Dialog:dialogid) {
	return Iter_Contains(Dialog, _:dialogid) ? true : false;
}

stock Dialog:CreateDialog(const name[], index = -1) {
	if(IsValidDialog(Dialog:index)) return -1;
	else if(index < 0) index = Iter_Free(Dialog);

	if(index > -1) {
		Iter_Add(Dialog, index);
		format(varDialog[index][ed_Name], 32, "dresp_%s", title);
	}
	return Dialog:index;
}

stock DestroyDialog(Dialog:dialogid)
	if(IsValidDialog(dialogid)) {
		Iter_Remove(Dialog, _:dialogid);
	}
	else return 0;
	return 1;
}

stock ChangeDialogStyle(Dialog:dialogid, style) {
	if(IsValidDialog(dialogid)) {
		varDialog[_:dialogid][ed_Style] = style;
	}
	else return 0;
	return 1;
}

stock SetDialogLeftButtonText(Dialog:dialogid, text[]) {
	if(IsValidDialog(dialogid)) {
		format(varDialog[_:dialogid][ed_ButtonL], 32, text);
	}
	else return 0;
	return 1;
}

stock SetDialogRightButtonText(Dialog:dialogid, text[]) {
	if(IsValidDialog(dialogid)) {
		format(varDialog[_:dialogid][ed_ButtonR], 32, text);
	}
	else return 0;
	return 1;
}

stock SetDialogCaptionText(Dialog:dialogid, text[]) {
	if(IsValidDialog(dialogid)) {
		format(varDialog[_:dialogid][ed_Title], 64, text);
	}
	else return 0;
	return 1;
}

stock SetDialogInfoText(Dialog:dialogid, text[]) {
	if(IsValidDialog(dialogid)) {
		format(varDialog[_:dialogid][ed_Info], 4096, text);
	}
	else return 0;
	return 1;
}

stock ShowDialogForPlayer(playerid, Dialog:dialogid, index = 0) {
	if(IsValidDialog(dialogid)) {
		index = _:dialogid;

		ShowPlayerDialog(
			playerid, index, varDialog[index][ed_Style],
			varDialog[index][ed_Title], varDialog[index][ed_Info],
			varDialog[index][ed_ButtonL], varDialog[index][ed_ButtonR]
		);
	}
	else return 0;
	return 1;
}

#pragma deprecated ShowPlayerDialog

#define DialogResponse:%0(%1) \
	forward dresp_%0(%1); public dresp_%0(%1)

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	if(0 <= funcidx(varDialog[dialogid][ed_Name])) {
		return CallLocalFunction(varDialog[dialogid][ed_Name], "ddds", playerid, response, listitem, inputtext);
	}
	return 0;
}

