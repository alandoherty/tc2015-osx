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

function addDevice(device) {
    console.log('adding device');
    $('#clientContainer').append('<div class="row client hdn device' + device.id + '" devID="' + device.id + '">' + '<div class="devContainer col-md-2">' +
                                    '<img src="images/devices/' + device.type + '.png" class="device"/>' +
                                    '</div>' +
                                    '<div class="name col-md-4">' + device.name + '</div>' +
                                    '<div class="work col-md-2">' + device.work + '</div>' +
                                    '<div class="status col-md-4"><span class="' + device.statusCode + '">' + device.statusText + '</span>' +
                                    '</div> </div>');

    // make sure to update the UI agter every addition
    setLineHeights();
    $('.app-clients').text(parseInt($('.app-clients').text()) + 1);

    $('.device' + device.id).fadeIn(1500);
}

function removeDevice(deviceID) {
    $('.device' + deviceID).fadeOut(800);
}

$(document).ready(function() {
    setLineHeights();

    var seconds = 0;
    var minutes = 0;
    /*
    var line = new ProgressBar.Circle('#progressBar', {
        strokeWidth: 4,
        color: '#3498db',
        text: {
            value: "00:00",
            style: {
                color: "#fff"
            }
        },
    });
    line.animate(1.0, {
        duration: 15000
    }, function() {
        console.log('Animation has finished');
    });*/

    var debugSupermesh = false;
    if (debugSupermesh) {
        var str = "";
        for(var k in supermesh)
            str += k + " : " + toString(supermesh[k]) + "\n";
        supermesh.message(str);
    }

    supermesh.on("opened", function(path) {
        supermesh.message("we have opened " + path);
    });

    setInterval(function() {
        seconds++;
        if(seconds < 10) {
            if(minutes < 10) {
                line.setText("0" + minutes + ":0" + seconds);
            } else {
                line.setText(minutes + ":0" + seconds);
            }
        } else if(seconds < 60) {
            if(minutes < 10) {
                line.setText("0" + minutes + ":" + seconds);
            } else {
                line.setText(minutes + ":" + seconds);
            }
        } else if(seconds == 60) {
            minutes++;
            seconds = 0;
            if(minutes < 10) {
                line.setText("0" + minutes + ":0" + seconds);
            } else {
                line.setText(minutes + ":0" + seconds);
            }
        }
    }, 1000);

    setAppStatus("online");
    setAppClients(1);
    setAppTask("testing this system");

    setWorkPercentage();

    addDevice({
        id: 2,
        type: "computer",
        name: "Test 123",
        work: "0%",
        statusCode: "error",
        statusText: "lost connection"
    })
});

$("#compilerButton").on('click', function() {
    if($(this).attr('aria-pressed') == "false") {
        $('#compilerOutput').slideDown(300);
    } else {
        $('#compilerOutput').slideUp(300);
    }
})