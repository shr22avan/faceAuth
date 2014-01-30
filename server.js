var fs=require('fs');
var exec=require('child_process').exec;
var http=require('http');
var express=require('express');
var app=express();
var server=http.createServer(app);
//var io=require('socket.io').listen(server);
var splitter=require('./splitter.js');
app.configure(function(){
    app.use(express.bodyParser());
});
app.get('/',function(req,res){
    console.log(req.url);
    fs.readFile(__dirname+'/index.html',function(err,data){
	if(err)
	{
	    console.log("Error Loading Index "+err);
	    return;
	}
	res.setHeader('Content-Type', 'text/html');
	res.end(data);
    });
});
app.get('/register',function(req,res){
    console.log(req.url);
    fs.readFile(__dirname+'/register.html',function(err,data){
	if(err)
	{
	    console.log("Error Loading Register "+err);
	    return;
	}
	res.setHeader('Content-Type','text/html');
	res.end(data);
    });
});
app.get('/login',function(req,res){
    console.log(req.url);
    fs.readFile(__dirname+'/login.html',function(err,data){
	if(err)
        {
            console.log("Error Loading Login "+err);
            return;
        }
	res.setHeader('Content-Type','text/html');
	res.end(data);
    });
});
app.get('/snapShot.js',function(req,res){
    console.log(req.url);
    fs.readFile(__dirname+'/snapShot.js',function(err,data){
	if(err)
	{
	    console.log("Error Loading snapShot JS "+err);
	    return;
	}
	res.setHeader('Content-Type','application/javascript');
	res.end(data);
    });
});
app.get('/batman.jpeg',function(req,res){
    console.log(req.url);
    fs.readFile(__dirname+'/batman.jpeg',function(err,data){
	if(err)
	{
	    console.log("Error in Loading batman Image "+err);
	    return;
	}
	res.setHeader('Content-Type','image/jpeg');
	res.end(data);
    });
});
app.post('/registerUser',function(req,res){
    fs.readFile(req.files.image.path,function(err,data){
	var imageName=req.files.image.name;
	if(!imageName)
	{
	    console.log("Error!");
	    res.redirect("/");
	    res.end();
	}
	else
	{
	    var newPath=__dirname+"/"+imageName;
	    fs.writeFile(newPath,data,function(err){
		if(err)
		{
		    console.log(err);
		    return;
		}
		res.redirect("/"+imageName);
	    });
	}
    });
});
/*app.post('/registerUser',function(req,res){
       var body="";
    req.on("data",function(chunk){
	body+=chunk;
    });
    req.on("end",function(){
	if(body!="")
	{
	    var hash=splitter.formValues(body);
	    console.log(hash["userRegName"]);
	    console.log(hash["userRegPhone"]);
	}
    });
    res.setHeader('Content-Type','text/plain');
    res.end("Mass");
});*/
/*app.post('/login',function(req,res){
    console.log(req.url);
    res.setHeader('Content-Type','text/plain');
    res.end("Over Mass");
});
app.get('/main.js',function(req,res){
    console.log(req.url);
    fs.readFile(__dirname+'/main.js',function(err,data){
	if(err)
	{
	    console.log("Error Loading Main Js "+err);
	    return;
	}
	res.setHeader('Content-Type','application/javascript');
	res.end(data);
    });
});*/
app.listen(3000);
console.log("Server running at 3000");
