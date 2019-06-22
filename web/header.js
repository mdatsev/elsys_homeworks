let idx = window.location.href.lastIndexOf('#');
let active = idx == -1 ? '#about' : window.location.href.substring(idx)
let cur = document.querySelector(`a[href="${active}"]`)
if (cur)
    cur.classList.add('active');

document.querySelectorAll('a[href*="#"]').forEach(function (el) {
    var targetId = el.hash,
        targetAnchor = document.getElementById(targetId.slice(1));
    if (!targetAnchor) return;
    var targetOffset = targetAnchor.offsetTop;
    el.addEventListener("click", function (e) {
        e.preventDefault();
        document.querySelectorAll("#nav li a")
            .forEach(e => e.classList.remove("active"));
        el.classList.add('active');
        window.scroll({
            top: targetOffset,
            behavior: 'smooth'
        });
    });
})

document.getElementById("header").style.width = document.body.clientWidth;