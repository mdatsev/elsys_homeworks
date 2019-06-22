{
    const videos = ["https://www.youtube.com/embed/oV4q3RCnP0s",
        "https://www.youtube.com/embed/A40Y04snrmg"
    ]
    let total = 3;
    const headerpx = document.getElementById("header").clientHeight + "px"
    let img = document.getElementById("gallery-image");
    let iframe = document.getElementById("gallery-video");
    document.getElementById("gallery-image").style.paddingTop = headerpx;
    document.getElementById("gallery-video").style.paddingTop = headerpx;
    let index = 0;

    function handleIndex(i) {
        if (i < 0) i = index = videos.length + total - 1;
        i %= videos.length + total;
        console.log(i)
        if (i >= total) {
            img.style.opacity = 0;
            iframe.style.opacity = 1;
            if (iframe.src != videos[i - total]) iframe.src = videos[i - total];
        } else {
            iframe.style.opacity = 0;
            img.style.opacity = 1;
            if (img.src != `gallery-${i}.jpg`) img.src = `gallery-${i}.jpg`;
        }
    }
    document.getElementById("gallery-prev").addEventListener("click", () => {
        handleIndex(--index)
    })
    document.getElementById("gallery-next").addEventListener("click", () => {
        handleIndex(++index);
    })
}