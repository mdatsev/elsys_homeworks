var modal = document.getElementById('myModal');

var span = document.getElementsByClassName("close")[0];
let last;
[].forEach.apply(document.getElementsByClassName("gamethumb"), [b => {
    let id = b.getAttribute("game")
    b.onclick = () => {
        document.getElementById(`game-${id}-canvas`).style.display = "block"
        last = b.getAttribute("game");
        eval(`game${id}()`)
        modal.style.display = "block";
    }
    b.src = `images/thumb${+id+1}.png`
}])

span.onclick = function () {
    document.getElementById(`game-${last}-canvas`).style.display = "none"
    modal.style.display = "none";
}

window.onclick = function (event) {
    if (event.target == modal) {
        document.getElementById(`game-${last}-canvas`).style.display = "none"
        modal.style.display = "none";
    }
}