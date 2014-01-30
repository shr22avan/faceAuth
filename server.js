var fs=require('fs');
var exec=require('child_process').exec;
var http=require('http');
var express=require('express');
var app=express();
var splitter=require('./splitter.js');
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

/*app.post('/register',function(req,res){
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
});
app.post('/login',function(req,res){
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
