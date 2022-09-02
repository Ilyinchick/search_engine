<h2 align="center"> Search engine </h2>
<body>
<dl>
<dt>Introduction</dt>
<dd>
Hi. This is my graduation project of the course C++ developer from Skillbox. <br>
This project can help with finding needed document from base of document with requests. <br>
</dd>
<dt>Used technology stack</dt>
<dd>
In this project i used following technology: <br>
<ul>
<li><b>C++ - </b> classes, structures, thread, containers such as vector, set and map, 
serialization and deserialization, exception, etc.</li>
<li><b>Google Test - </b> also I added Google Testing C++ Framework to this project 
to track if my classes are working correctly. </li>
<li><b>JSON for modern C++ - </b> to serialize and deserialize data in this project 
I used nlohmann::json library</li>
<li><b>GitHub - </b> to control versions of this project I placed it on GitHub.</li>
</ul>
</dd>
<dt>Instructions to run the project</dt>
<dd>
<ul>
<li>Download and extract this project. </li>
<li>Download and extract <a href="https://github.com/nlohmann/json"> <b>JSON for modern C++</b> </a>
into root folder of project. Make sure that references in CMakeList.txt are valid for 
your paths. <br></li>
<li>To run test you also need to download and extract <a href="https://github.com/google/googletest"> 
<b>Google Test Framework for C++</b></a> in root folder. 
In that case also check references in CMakeList.txt <br></li>
<li>I used absolute paths in this project, so to run project correctly you need to make sure 
that all global paths in project are correct.
<br> Files to check: 
<ul>
<li><a href="manage/config.json">Config.json</a> file in "manage" folder.</li>
<li>Global std::string in <a href="include/ConverterJSON.h">ConverterJSON.h</a> - 
CONFIG_PATH, REQUESTS_PATH, ANSWERS_PATH ("include" folder).</li>
</ul>
</li>
</ul>

If all is correct, you can run project in your IDE. <br>
In this project I used MinGW compiler.
</dd>

</dl>
</body>