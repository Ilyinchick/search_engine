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

<li>Open this project in your IDE and build it with CMake (you can also do this in Terminal).</li>

<li>After building and compiling project an executable file of the project will be created in the
<a href="executable">"executable"</a> folder. The <a href="executable/manage">"manage"</a>
 and <a href="executable/resources">"resources"</a> folders should also be there. </li>

<li>Now you can run this program. If you want to add some txt files to search, you need to 
write paths to those files in file 
<a href="executable/manage/config.json">config.json</a> ("manage" folder). 
If you want to use relative paths to your files in <a href="executable/manage/config.json">config.json</a> 
recommended to put it in <a href="executable/resources">"resources"</a> folder and 
write paths in "./resources/name_of_your_file.txt" format.</li>

<li>In file <a href="executable/manage/requests.json">requests.json</a> ("manage" folder) you can add more requests
to search and adjust they to your needs. </li>

</ul>

If all is correct, you can run project in your IDE. <br>
In this project I used MinGW compiler.
</dd>

</dl>
</body>