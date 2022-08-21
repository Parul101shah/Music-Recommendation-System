const btn =document.querySelector('.ColorButton');

const colorgrid =document.querySelector('.Colorgrid');
const colorValue =document.querySelector('.ColorValue');

btn.addEventListener('click' , async() =>{

    const color= chrome.storage.sync.get('color',({color})=>{
        console.log('color',color);
    });

    let[tab]=await chrome.tabs.query({active :true,currentWindow :true}); 

    chrome.scripting.executeScript({
        target : {tabId : tab.id},
        function : pickColor,
    },async(injectionResults) =>{
        const [data] =injectionResults;
        if(data.result)
        {
            const color= data.result.sRGBHex;
            colorgrid.style.backgroundColor = color;
            colorValue.innerText=color;

            try{
                await navigator.clipboard.writeText(color);
            }
            catch(err)
            {
                console.error(err);
            }

           
            console.log(colorgrid);
        }
    });
});

async function pickColor()
{
    try{

        const eyeDropper =new EyeDropper();
        return await eyeDropper.open();
      
    }
    catch(err)
    {
        console.error(err);
    }
}
