var workPercentageChart = [27, 25.3, 28];

function setAppStatus(status) {
    $('.app-status').text(status);
}

function setAppClients(number) {
    $('.app-clients').text(number);
}

function setAppTask(task) {
    $('.app-task').text(task);
}

function setLineHeights() {
    var lineHeight = $('#clientContainer').children().children().height();
    $('#clientContainer .client').css('line-height', lineHeight + "px");
}

function setWorkPercentage() {
    $('#clientContainer').children('.client').each(function () {
        var devID = $(this).attr('devID') - 1;
        $(this).children('.work').text(workPercentageChart[devID] + "%");;
    });
}

$(document).ready(function() {
    setLineHeights();

    var line = new ProgressBar.Line('#progressBar');
    line.animate(1.0, {
        duration: 800
    }, function() {
        console.log('Animation has finished');
    });

    setAppStatus("online");
    setAppClients(1);
    setAppTask("testing this system");

    setWorkPercentage();
});