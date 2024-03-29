const targetList = document.getElementById('drink-list');
var pageLast = 1;
var currentPage = 1;
var pageWidth = 1;

function order(n){
  console.log(n);
}

function page(d){
  const pageIndicator = document.getElementById('current-page');
  const scrollWrapper = document.getElementById('scroll-wrapper');

  pageWidth = scrollWrapper.clientWidth;
  console.log(pageWidth);

  console.log("scroll");
  scrollWrapper.scrollLeft = pageWidth*(currentPage-1) + pageWidth*d;
  currentPage += d;
  pageIndicator.innerHTML = currentPage;
  if(currentPage == pageLast){
    document.getElementById('pageNext').classList.add('button-inactive')
      document.getElementById('pagePrev').classList.remove('button-inactive')
  }else if(currentPage == 1){
    document.getElementById('pagePrev').classList.add('button-inactive')
    document.getElementById('pageNext').classList.remove('button-inactive')
  }else{
    document.getElementById('pagePrev').classList.remove('button-inactive')
    document.getElementById('pageNext').classList.remove('button-inactive')
  }
}


function makeList(drinks){
  const list = targetList;
  const numberOfPages = Math.ceil(drinks.length * 0.16)
  pageLast = numberOfPages;
  console.log(numberOfPages);
  targetList.style.width = (100 * numberOfPages) + "vw";
  for(let i = 0; i < numberOfPages; i++){
    const page = document.createElement("DIV");
    page.classList.add("page")
    for(let j = 0; j < 6; j++){
      let index = j+i*6
      console.log(index);
      if(!drinks[index]) continue;



      const listItem = document.createElement("LI");
      listItem.classList.add("list-"+index)
      listItem.innerHTML = ("<p>" + drinks[index].name + "</p>");
      const image = document.createElement("IMAGE");
      image.src = drinks[index].imagePath;
      listItem.addEventListener("click", function(){
        order(drinks[index].recipe);
      });
      listItem.append(image);
      page.append(listItem);
    }
    list.append(page)
  }
}

function init () {
  const drinks = JSON.parse(this.response);
  console.log("Hello");
  makeList(drinks.drinks);
}

var oReq = new XMLHttpRequest();
oReq.addEventListener("load", init);
oReq.open("GET", "./drinks.json");
oReq.send();
