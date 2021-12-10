$(document).ready(function () {
    $("#AddMoreTextBox").click(function () {
        $("#InputsWrapper").append('<input type="number" name=number value=100><br><br>');
    });
});