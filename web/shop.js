let itemsData = [{
        id: "duduk",
        name: "Duduk",
        price: 100
    },
    {
        id: "chasovnik",
        name: "Strap from the watch",
        price: 60
    },
    {
        id: "art",
        name: "Art pack",
        price: 299
    },
    {
        id: "book",
        name: "The holy trinity book",
        price: 60
    },
    {
        id: "astronaut",
        name: "Space suit",
        price: 12000000
    },
    {
        id: "egg-shirt",
        name: "Egg T-shirt",
        price: 29
    },
    {
        id: "smile-shirt",
        name: "Smile T-shirt",
        price: 29
    },
    {
        id: "anime",
        name: "Anime",
        price: 9.99
    },
    {
        id: "eggs",
        name: "A pack of eggs",
        price: 5.49
    },
    {
        id: "frame",
        name: "Framed picture",
        price: 9.49
    },
    {
        id: "globe.gif",
        name: "Snow globe",
        price: 15.49
    },
    {
        id: "manga",
        name: "Comic book by Svetli",
        price: 100000
    },
    {
        id: "mona",
        name: "Mona lisa adaptation",
        price: 9999
    },
    {
        id: "outfit",
        name: "Cute outfit",
        price: 99
    },
    {
        id: "pastel",
        name: "Pastel painting",
        price: 200
    },
    {
        id: "sheini",
        name: "Sleigh lessons",
        price: "10"
    },
    {
        id: "shrek",
        name: "Shrek 5",
        price: 15
    },
    {
        id: "skydiving",
        name: "Skydiving",
        price: 215
    },
    {
        id: "sleeping",
        name: "Sleeping beauty painting",
        price: 12000
    },
    {
        id: "tattoo",
        name: "Tattoo",
        price: 99.99
    },
    {
        id: "thinking",
        name: "Spheres mind teaser",
        price: 99.99
    },
    {
        id: "truck",
        name: "Truck",
        price: 55000000
    },
]

let placeholderDescription = `Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed semper ut eros non viverra. Suspendisse pulvinar laoreet ante. Aenean ornare elit in tellus semper bibendum. Phasellus laoreet enim mi, sit amet mollis mi lacinia eget. Donec venenatis massa sem. Curabitur non enim nec lectus auctor luctus. Etiam arcu elit, ornare et suscipit id, aliquam a sapien. Suspendisse ut posuere lorem.
Quisque sagittis est vitae eleifend pretium. Donec accumsan lectus vel sodales rhoncus. Quisque elit arcu, semper sed lobortis et, hendrerit non neque. Fusce sit amet purus ipsum. Nam eu enim sed quam volutpat condimentum condimentum ut lectus. Nulla convallis lacus id sagittis vehicula. Suspendisse tristique, elit vitae pulvinar tempus, dolor massa gravida metus, quis vehicula ex augue vitae arcu. Quisque rhoncus dui pharetra risus egestas, ut tincidunt urna feugiat. Nam aliquam, tellus eget aliquet rutrum, nunc mi mollis felis, a dignissim elit orci at diam. Nunc ullamcorper massa nisl. Proin tempor placerat diam, vel efficitur libero dignissim sit amet.`

let wrapper = document.getElementById("wrapper");

const path = id => `images/${id}${id.includes('.') ? '' : '.jpg'}`

for (let i = 0; i < itemsData.length; i++) {
    /*let box = document.createElement('div');
    box.className = "box";
    let title = document.createElement('h1');
    title.className = "title";
    title.innerText = itemsData[i] && itemsData[i].name;
    box.appendChild(title);
    let price = document.createElement('h2');
    price.className = "price";
    price.innerText = itemsData[i] && "$" + itemsData[i].price;
    box.appendChild(price);
    let img = document.createElement('img');
    img.className = "img";
    img.setAttribute('src', path(itemsData[i] ? itemsData[i].id : i + 1));
    box.appendChild(img)
    let btn = document.createElement('button');
    btn.className = "open";
    btn.innerText = "Buy";
    btn.setAttribute("id", i);
    box.appendChild(btn);
    wrapper.appendChild(box)*/
    var t = document.querySelector('#item');

    var clone = document.importNode(t.content, true);
    clone.querySelector("img").setAttribute('src', path(itemsData[i].id));
    clone.querySelector("img").onclick = () => {
        document.getElementById("item-description").innerText = itemsData[i].description || placeholderDescription;
        document.getElementById("item-image").setAttribute("src", path(itemsData[i].id))
        modal.style.display = "block";
    };
    clone.querySelector(".item-description").innerText = itemsData[i].name
    clone.querySelector(".item-price").innerText = itemsData[i].price
    clone.querySelector("button").onclick = () => {
        buyModal.style.display = "block"
    }
    wrapper.appendChild(clone);
}


// Get the modal
var modal = document.getElementById('myModal');
var buyModal = document.getElementById('buyModal');
// Get the button that opens the modal
var btns = document.getElementsByClassName("open");

// When the user clicks on the button, open the modal 
// When the user clicks on <span> (x), close the modal
[].forEach.apply(
    document.getElementsByClassName("close"), [
        closeBtn => closeBtn.onclick =
        () => [].forEach.apply(
            document.getElementsByClassName("modal"), [
                md => md.style.display = "none"
            ])
    ])

// When the user clicks anywhere outside of the modal, close it
window.onclick = function (event) {
    if (event.target == modal) {
        modal.style.display = "none";
    }
    if (event.target == buyModal) {
        buyModal.style.display = "none";
    }
}