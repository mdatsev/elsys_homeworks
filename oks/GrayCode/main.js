let colors = {
    background: 0,
    gridLines: "white",
    variables: ["#FF0000",
        "#00FFFF", "#00FF00", "#FFFF00", "#FF00FF",
        "#800000", "#F9BC08", "#C0C0C0", "#FE83CC",
        "#800080", "#808000", "#008080", "#808080",
        "#008000", "#800000", "#FFFFFF", "#000080"]
};
let hoveredVar = -1;
let hoveredCell = -1;

let nVariables = 4;
let nCells = 2 ** nVariables;
let line_width = 1.5;

let scaleFactor = 1.0;
let translateX = 0.0;
let translateY = 0.0;
let zoomSensitivity = 0.001;

let alternateSides;

let gridWidth;
let gridHeight;
let gridY;

let varsTextSize = 32;

function setup() {
    gridWidth = windowWidth - 2;
    gridY = windowHeight / 2;
    gridHeight = min(gridWidth / nCells, windowHeight / 2 - 2);
    zoomLocation = { x: 0, y: windowHeight / 2 };
    angleMode(DEGREES);
    createCanvas(windowWidth, windowHeight);
    background(colors.background);
    createGUI();
}

function draw() {
    translate(translateX, translateY);
    scale(scaleFactor);
    drawGrid();
    drawLegend();
}

function mouseWheel(event) {
    event.preventDefault();
    translateX -= mouseX;
    translateY -= mouseY;
    let delta = 1 - event.delta * zoomSensitivity;
    scaleFactor *= delta;
    translateX *= delta;
    translateY *= delta;
    translateX += mouseX;
    translateY += mouseY;
}

function mouseDragged() {
    translateX += mouseX - pmouseX;
    translateY += mouseY - pmouseY;
}

function clearDraw() {
    background(colors.background);
    createGUI();
    createLayout();
}

function drawGrid() {
    strokeWeight(line_width / scaleFactor);
    background(colors.background);
    stroke(colors.gridLines);
    line(0, gridY, gridWidth, gridY);
    line(0, gridY + gridHeight, gridWidth, gridY + gridHeight);
    for (let i = 0; i < nCells + 1; i++) {
        let x1 = i * (gridWidth / nCells);
        line(x1, gridY, i * (gridWidth / nCells), gridY + gridHeight);
        if (hoveredCell == i) {
            stroke("white");
            fill("white");
            rect(x1, gridY, gridWidth / nCells, gridHeight);
        }
    }

    let curveHeight = 2;

    let drawVariable = (n, color, bottomSide = true) => {
        let p1 = { x: 1 / (2 ** (n + 1)) * gridWidth, y: gridY };
        let c1 = { x: p1.x, y: p1.y + gridWidth / (2 ** n) * curveHeight };
        let p2 = { y: p1.y };
        let c2 = { y: c1.y };;
        if (bottomSide) {
            c1.y = p1.y - (c1.y - p1.y) + gridHeight;
            c2.y = p2.y - (c2.y - p2.y) + gridHeight;
            p1.y += gridHeight;
            p2.y += gridHeight;
        }
        noFill();
        stroke(color);
        if (n == 0) {
            p2.x = gridWidth;
            c2.x = p2.x;
            c1.y = c2.y = p1.y + gridWidth / 2 * curveHeight;
            if (bottomSide) {
                c1.y = c2.y = p1.y - gridWidth / 2 * curveHeight + gridHeight;
            }
            curve(c1.x, c1.y, p1.x, p1.y, p2.x, p2.y, c2.x, c2.y);
            return;
        }
        for (let i = 3; i < 2 ** (n + 1); i += 2) {
            p2.x = i / (2 ** (n + 1)) * gridWidth
            c2.x = p2.x;
            if ((i - 3) % 4 == 0) {
                curve(c1.x, c1.y, p1.x, p1.y, p2.x, p2.y, c2.x, c2.y);
            }
            else {
                p1.x = p2.x;
                c1.x = c2.x;
            }
        }
    };

    for (let i = 0; i < nVariables; i++) {
        drawVariable(i, colors.variables[nVariables - i - 1], alternateSides.checked() ? i % 2 : 0);
    }
}

function grayAt(number, position) {
    return ((number ^ (number >>> 1)) & (1 << position)) != 0 ? 1 : 0;
}

function createGUI() {
    let varsInp = createInput(nVariables);
    $(varsInp.elt).attr('placeholder', "Number of variables");
    varsInp.position(0, 0);

    startBtn = createButton('Start');
    startBtn.position(varsInp.width, 0);

    //startBtn.size(sidebar_width - LABEL_MARGIN, sidebar_spacing * 2);
    startBtn.mousePressed(() => {
        //running = !running;
        //$(startBtn.elt).text(running ? 'pause' : 'start');

        if (!isNaN(parseFloat(varsInp.value()))) {
            newnVariables = parseFloat(varsInp.value());
            newnCells = 2 ** newnVariables;
            if (newnCells > 10000) {
                if (!window.confirm(`You are about to create ${newnCells} cells. This might lag your browser. Are you sure?`)) {
                    return;
                }
            }
            nVariables = newnVariables;
            nCells = newnCells;
            gridHeight = min(gridWidth / nCells, windowHeight / 2 - 2);
        }
    });

    alternateSides = createCheckbox("alternate sides", false);
    $(alternateSides.elt).css("color", "white");
    alternateSides.position(0, 22);

    elems_created = true;
}

function mouseMoved() {
    if ((mouseY - translateY) / scaleFactor > gridY &&
        (mouseY - translateY) / scaleFactor < gridHeight + gridY)
        hoveredCell = Math.floor((mouseX - translateX) / scaleFactor / gridWidth * nCells);
    else
        hoveredCell = -1;
}

function drawLegend() {
    resetMatrix();
    for (let i = 0; i < nVariables; i++) {
        fill(colors.variables[i % colors.variables.length] || "white");
        noStroke();
        textAlign(RIGHT, TOP);
        textSize(varsTextSize);
        let x = windowWidth - i * varsTextSize * 1.25 - varsTextSize;
        text("X", x, 0);
        textSize(varsTextSize / 2);
        textAlign(LEFT, BOTTOM);
        text(i, x, varsTextSize);
        textAlign(CENTER, TOP);
        textSize(varsTextSize);
        text(grayAt(hoveredCell, i), x, varsTextSize)
    }
}