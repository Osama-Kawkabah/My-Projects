let imgrandom = document.querySelector(".box-img-left #box-img");
let BackClickAli = document.querySelectorAll(".backgrund-hendal span");

// ----------------nav---------------------
let ourSkills = document.querySelectorAll(".our-skills .box-skills .box-width");
let zero = document.getElementById("Home");
let one = document.getElementById("About");
let two = document.getElementById("Program");
let three = document.getElementById("img-popup");
let fure = document.getElementById("data-years");
let five = document.getElementById("users-Masseg");
let six = document.getElementById("box-form");

let arryNav = [zero, one, two, three, fure, five, six];

let boxClick = document.querySelectorAll(".box-click");

window.onscroll = () => {
  if (window.scrollY >= arryNav[2].offsetTop - 300) {
    ourSkills.forEach(skill => {
      skill.style.width = skill.dataset.widskills;
    });
  }

  for (let i = 0; i < arryNav.length; i++) {
    if (scrollY >= arryNav[i].offsetTop - 300) {
      if (`${boxClick[i].dataset.section}` == `.${arryNav[i].className}`) {
        boxClick.forEach(e => {
          e.classList.remove("active");
        });
        boxClick[i].classList.add("active");
        console.log("Yes");
      } else {
        boxClick[i].classList.remove("active");
      }
    }
  }
};

// ----------------End-nav---------------------

//  loStoColor-ShowBullets
let ShowBullets = document.querySelectorAll(".Stop-nav span");
let Listshow = false;
let butyes = document.querySelector(".Stop-nav .yes");
let butNo = document.querySelector(".Stop-nav .no");
let DeleBullet = document.querySelector(".right-click");

ShowBullets.forEach(show => {
  show.onclick = span => {
    ShowBullets.forEach(e => {
      e.classList.remove("active");
    });

    span.target.classList.add("active");
    if (ShowBullets != null) {
      if (butyes.classList.contains("active")) {
        DeleBullet.style.display = "block";
        Listshow = true;
      }
      if (butNo.classList.contains("active")) {
        DeleBullet.style.display = "none";
        Listshow = false;
      }
      localStorage.setItem("ShowBullets", Listshow);
    }
  };
});

let showBut = localStorage.getItem("ShowBullets");
if (showBut == "true") {
  butyes.classList.add("active");
  butNo.classList.remove("active");
  DeleBullet.style.display = "block";
} else if (showBut == "false") {
  butNo.classList.add("active");
  DeleBullet.style.display = "none";
  butyes.classList.remove("active");
}

// loStoColor-Color
let loStoColor = localStorage.getItem("Color-Page");
if (loStoColor != null) {
  document.documentElement.style.setProperty("--Secondaryline", loStoColor);
  document.querySelectorAll(".list-color-ul li").forEach(ele => {
    ele.classList.remove("active");
    if (ele.dataset.color === loStoColor) {
      // -----h1-color-hover-------
      let textcolor = document.querySelector(".list-color h1");
      textcolor.addEventListener("mouseover", () => {
        textcolor.style.background = "#FF6347";
      });
      textcolor.addEventListener("mouseout", () => {
        textcolor.style.background = "white";
      });
      // ------------
      ele.classList.add("active");
    }
  });
}
//End-loStoColor-Color
// Click-Setting
var iconElement = document.querySelector(".setting");

iconElement.onclick = () => {
  let boxleftsetting = document.querySelector(".box-left-setting");
  boxleftsetting.classList.toggle("move");
};
// End-Setting

// for-loop-li
const listColor = document.querySelectorAll(".list-color-ul li");

listColor.forEach(li => {
  li.onclick = function(e) {
    document.documentElement.style.setProperty(
      "--Secondaryline",
      e.target.dataset.color
    );

    localStorage.setItem("Color-Page", e.target.dataset.color);

    e.target.parentElement.querySelectorAll(".active").forEach(ele => {
      ele.classList.remove("active");
    });
    e.target.classList.add("active");
  };
});

// الحصول على جميع الأزرار
let BackClickYes = document.querySelector(".yes");
let BackClickNo = document.querySelector(".no");
let handlebackran = true;
let localhandlebackran = localStorage.getItem("handle-backran");
let localhandimg = localStorage.getItem("src-img");

if (localhandlebackran !== null) {
  BackClickAli.forEach(e => {
    e.classList.remove("active");
  });
  if (localhandlebackran === "true") {
    handlebackran = true;
    document.querySelector(".backgrund-hendal .yes").classList.add("active");
  } else {
    handlebackran = false;
    document.querySelector(".backgrund-hendal .no").classList.add("active");
    imgrandom.src = localhandimg;
    imgrandom.style.width = "90%";
    imgrandom.style.height = "90%";
    imgrandom.style.borderRadius = "50%";
  }
}
let handleiInterval;
BackClickAli.forEach(spans => {
  spans.addEventListener("click", () => {
    BackClickAli.forEach(e => {
      e.classList.remove("active");
    });
    spans.classList.add("active");
    if (BackClickYes.classList.contains("active")) {
      handlebackran = true;
      moveImg();
      let img = "img/astrocat.png";
      imgrandom.src = img;
    }
    if (BackClickNo.classList.contains("active")) {
      handlebackran = false;
      clearInterval(handleiInterval);
    }
    localStorage.setItem("handle-backran", handlebackran);
  });
});

// Images-Random

let arrayimg = ["cont-hed-4", "cont-hed-2", "cont-hed-3", "cont-hed-2"];

function moveImg() {
  if (handlebackran === true) {
    handleiInterval = setInterval(() => {
      let x = Math.floor(Math.random() * arrayimg.length);
      imgrandom.src = `img/${arrayimg[x]}.png`;
    }, 1000);
  }
}
moveImg();
// click-random-img
imgrandom.onclick = () => {
  let arrayimg = "img/astrocat.png";
  imgrandom.src = `${arrayimg}`;
};
//End- Images-Random

// -----------------------------
let imabacgrund = document.querySelectorAll(".ima-bacgrund img");
imabacgrund.forEach(img => {
  img.addEventListener("click", function() {
    BackClickNo.click();
    // --------------------------------
    imgrandom.src = `${img.src}`;
    imgrandom.style.width = "90%";
    imgrandom.style.height = "90%";
    imgrandom.style.borderRadius = "50%";
    localStorage.setItem("src-img", imgrandom.src);
  });
});

let ImgOverlay = document.querySelectorAll(".Img-overlay img");

ImgOverlay.forEach(img => {
  img.addEventListener("click", e => {
    // Create => div
    let ImgPopup = document.createElement("div");
    ImgPopup.className = "img-popup-click";

    // Create-Child => div
    let ImgPopupbox = document.createElement("div");
    ImgPopupbox.className = "ImgPopupbox";

    // Create => img
    let Imgbox = document.createElement("img");
    Imgbox.src = img.src;
    Imgbox.style.background = "#0f0a33";
    ImgPopup.appendChild(ImgPopupbox);
    ImgPopupbox.appendChild(Imgbox);
    document.body.appendChild(ImgPopup);

    if (img.alt !== "") {
      let textAlt = document.createElement("span");
      textAlt.className = "text-alt";
      let alt = document.createTextNode(img.alt);
      textAlt.appendChild(alt);
      ImgPopup.appendChild(textAlt);
    }

    let closeButten = document.createElement("div");
    closeButten.className = "closeButten";
    let iconButten = document.createTextNode("x");
    closeButten.appendChild(iconButten);
    ImgPopupbox.appendChild(closeButten);

    closeButten.onclick = () => {
      ImgPopup.remove();
    };
  });
});

let arryImg = [
  "img/Users/img_avatar.png",
  "img/Users/img_avatar1.png",
  "img/Users/img_avatar2.png",
  "img/Users/img_avatar3.png",
  "img/Users/img_avatar4.png"
];
let arryName = ["OsamaAli", "Mohammed-Saleh", "Ali", "Nasser", "Woman"];

let boxUsers = document.querySelectorAll(".box-users img");
let boxText = document.querySelectorAll(".box-users p");
let boxTexth1 = document.querySelectorAll(".box-users h1");

boxTexth1.forEach((texth1, index) => {
  texth1.innerHTML = arryName[index];
});
boxUsers.forEach((img, index) => {
  img.src = arryImg[index];
});

let NavboxClick = document.querySelectorAll(".right-click .box-click");

NavboxClick.forEach(section => {
  section.addEventListener("click", e => {
    document
      .querySelector(e.target.dataset.section)
      .scrollIntoView({ behavior: "smooth" });
  });
});

let sideCercles = document.querySelectorAll(".box-click");

sideCercles.forEach(cercles => {
  cercles.onclick = e => {
    sideCercles.forEach(but => {
      but.classList.remove("active");
    });
    e.target.classList.add("active");
  };
});

let ResetOptions = document.querySelectorAll(".reset-options span");
let Reset = document.querySelector(".reset-options .yes");

ResetOptions.forEach(reset => {
  reset.onclick = () => {
    ResetOptions.forEach(e => {
      e.classList.remove("active");
    });
    reset.classList.add("active");
  };
});
Reset.onclick = () => {
  localStorage.clear();
  location.reload();
};
