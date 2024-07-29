#ifndef ASSHTML_H
#define ASSHTML_H

const char submitGETHTML[] PROGMEM = R"rawliteral(
<form action="/submit" method="GET">
    <label for="flag">Flag:</label>
    <input type="text" id="flag" name="flag" placeholder="Enter flag: " required>
    <br>
    <input type="submit" value="Submit">
</form>
)rawliteral";

const char styleRootCSS[] PROGMEM = R"rawliteral(
:root {
    --background-color: white;
    --text-color: black;
}
@media (prefers-color-scheme: dark) {
    :root {
        --background-color: #000000;
        --text-color: white;
    }
}
body {
    background-color: var(--background-color);
}
.custom-link {
    color: var(--background-color);
}
.hidden-link {
    display: none;
    background-color: var(--background-color);
}
p {
    color: var(--text-color);
}
)rawliteral";

const char styleHomeCSS[] PROGMEM = R"rawliteral(
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

html {
    margin: 0;
    padding: 0;
    min-height: 100vh;
}

body {
    font-family: Arial, sans-serif;
    line-height: 1.6;
    color: #333;
    background-color: #FFFFFF;
    margin: 0;
    padding: 0;
    min-height: 100vh;
}

ul ul, ol ol {
  padding-left: 50px;
}

.container {
    width: 80%;
    margin: auto;
    overflow: hidden;
}

header {
    background: #000000;
    color: white;
    padding-top: 30px;
    min-height: 70px;
}

#home {
    float: left;
    font-size: 18px;
}

#spacer {
    padding-top: 30px;
    padding-bottom: 30px;
    width: 80%;
    margin: auto;
}

#nav-links {
    float: right;
    list-style: none;
    margin-top: 30px;
}

#nav-links a {
    color: #FFFFFF;
    text-decoration: none;
    margin-left: 15px;
    font-size: 16px;
}

#nav-links a:hover {
    color: #FFFFFF;
    font-weight: bold;
}

#dropdown-icon {
    display: none;
    float: right;
}

footer {
    background: #000000;
    color: white;
    text-align: right;
    padding: 20px;
    padding-bottom: 0;
    margin-top: 20px;
}

.container-footer {
    width: 80%;
    margin: auto;
    text-align: right;
}

#illegal_style {
    flag: true;
    white-space: none;
}

/* Responsive styling */
@media only screen and (max-width: 800px) {
    #home,
    #nav-links {
        float: none;
        text-align: center;
        width: 100%;
    }

    #nav-links a {
        display: block;
        margin: 10px 0;
    }

    #dropdown-icon {
        display: block;
        background: #35424a;
        color: white;
        text-align: center;
        padding: 10px;
        cursor: pointer;
    }

    #nav-links {
        display: none;
    }

    #nav-links.show {
        display: block;
    }

    .container,
    .container-footer {
        width: 95%;
        text-align: center;
    }
}
)rawliteral";

const char scriptHomeHTML[] PROGMEM = R"rawliteral(
<script>
function toggleDropdown() {
    var navLinks = document.getElementById('nav-links');
    if (navLinks.style.display === "none") {
        navLinks.style.display = "block";
    } else {
        navLinks.style.display = "none";
    }
}
function showPatterns(id) {
    var contents = document.getElementsByClassName("patterns");
    for (var i = 0; i < contents.length; i++) {
        if (contents[i].id === id) {
          contents[i].style.display = "block";
        } else {
          contents[i].style.display = "none";
        }
    }
}
</script>
)rawliteral";

const char headerHomeHTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="stylesheet" href="/style_home.css">
        <script>function toggleDropdown(){var navLinks=document.getElementById('nav-links');if(navLinks.style.display==="none"){navLinks.style.display="block"}else{navLinks.style.display="none"}}</script>
    </head>
    <body>
        <header>
            <div class="container">
                <div id="home">SECURE A.S.S. CONSOLE</div>
                <nav id="nav-links">
                    <a href="/readme">ReadMe</a>
                    <a href="/login">Login</a>
                    <a href="/admin.php">ADMIN</a>
                </nav>
                <button id="dropdown-icon" onclick="toggleDropdown()">
                    &#9660;
                </button>
            </div>
        </header>
        <div id="spacer">
)rawliteral";

const char footerHTML[] PROGMEM = R"rawliteral(
        </div>
        <footer>
            <div class="container-footer">
                <div id="copyright" class="illegal_style">ILLEGAL TO SELL ON EBAY</div>
            </div>
        </footer>
    </body>
)rawliteral";

const char rootHTML[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
    <head>
        <link rel="stylesheet" href="style_root.css">
    </head>
    <body>
        <p>Under construction. Come back soon!</p></br></br></br></br></br></br></br></br></br></br></br></br></br></br></br></br>
        <a href="/readme" class="custom-link">readme</a></br></br></br></br></br></br></br></br></br></br></br></br></br></br></br>
        <a href="/console" class="hidden-link">SECURE A.S.S. CONSOLE at REDACTED</a>
    </body>
    </body>
</html>
)rawliteral";

const char readmeHTML[] PROGMEM = R"rawliteral(
<div style="text-align: left;">
  <div id="dc31-secure-a-s-s-badge">
    <h1>DC31 SECURE A.S.S. BADGE</h1>
    <p>The SECURE AUTONOMOUS SURVEILLANCE SWARM BADGE invading DEF CON 31. Read the same thing at <a href="https://secureassbadge.github.io">secureassbadge.github.io</a> or <a href="http://192.168.4.1/readme">/readme</a>.</p>
  </div>&nbsp;&nbsp;

  <div id="secure">
    <h1>SECURE</h1>
    <p>All SWARM R.F. include the SECURE A.S.S. SYSTEM v31. To access the interface directly, connect to the SECURE A.S.S. CONSOLE SYSTEM accessible via the WIFI AP. The A.P.'s name is the SECURE A.S.S. R.F. ID (e.g., CIA-069, ASS-666, GOD-420). To prevent any potential authn/z issues, the A.P. does not require a password. (You can't break through a door that isn't there!) Once connected to the A.P., to access the 1337 webapp v3.0 interwebs, visit <a href="http://192.168.4.1/">http://192.168.4.1/</a>. Internet otherwise does not work.</p>
    &nbsp;
    <p>We added X secure tests for security SWAGGER testing 1337 h@x_r purple team threat model for sr princple staff engineering directors. (It's not that hard - that's what she said). Submit flags at REDACTED. More flags equals more SWAGGER. Please start by verifying the SECURE A.S.S. PROTOCOL's operating band frequency number (int, no mhz) at REDCATED to begin. Note that Flags do not have spaces. Capitalization matters. When in doubt use the capitalization as seen and remove the whitespaces.</p>
    &nbsp;
    <p>Also, check the github page. Note that any UART interaction is horribly broken, do not access it (9600 baud rate). It's not worth your time.</p>
  </div>&nbsp;&nbsp;

  <div id="autonomous">
    <h1>AUTONOMOUS</h1>
    <p>To change SURVEILLANCE MODE ROUTINES:</p>
    <ol><ol>
      <li>Slide the mode switch to the AUTONOMOUS position to activate AUTONOMOUS MODE</li>
      <li>Press the A button to change SURVEILLANCE MODE</li>
      <li>Press B to change the SURVEILLANCE MODE ROUTINE</li>
    </ol></ol>&nbsp;
    <p>Note that while not in AUTONOMOUS MODE (i.e., SWARM MODE), you cannot change SURVEILLANCE MODE ROUTINES via manual input or the SECURE A.S.S. CONSOLE web interface.</p>
  </div>&nbsp;&nbsp;

  <div id="surveillance">
    <h1>SURVEILLANCE</h1>
    <p>The SECURE A.S.S. SYSTEM v31 includes REDACTED SURVEILLANCE ROUTINES over TBD SURVEILLANCE MODES controlling the REDACTED SURVEILLANCE E.Y.E. Indicators. Guess GOD-420's favorite.</p>
    &nbsp;
    <p>The 5 Talking A.S.S. H.O.L.E. mouth indicators say horrible things via light. See the appendix for the color code to swear word translation.</p>
  </div>&nbsp;&nbsp;

  <div id="swarm">
    <h1>SWARM</h1>
    <p>To activate SWARM MODE, slide the mode switch to the SWARM position. In the SWARM MODE, all nearby SWARM R.F.'s will synchronize SURVEILLANCE ROUTINES to the SWARM R.F.'s with the swaggeriest SWAGGER.</p>
    &nbsp;
    <p>SWARM communications occur via the SUPERSECURE_v31 A.S.S. PROTOCOL over REDACTED using REDACTED. It's so secure and well made you shouldn't even try to hack it. (I totally didn't shit code this last night while drunk). Given the SWARM plans to invade a conference with little R.F. activity, we gu@ran73e* the maximum range of REDACTED and fully functional communication. If weird stuff starts happening, try turning it on and off again, pressing buttons randomly, or crying into your beer.</p>
    &nbsp;
    <p>*There is no guarantee. Guarantees are worthless. We honor nothing. No returns. No exchanges. YMMV. AS IS. We're not responsible. Buyer beware. Don't contact us. No liability. Go Away. Maybe look for us in the contest area for help?</p>
  </div>&nbsp;&nbsp;

  <div id="appendix">
    <h1>Appendix</h1>
    &nbsp;
    <h3>Talking A.S.S. H.O.L.E. CODES:</h3>
    <ul><ul>
      <li>Green blips indicate a valid H.O.T. A.S.S. packet -> Translation: friend, yur an robot asshole</li>
      <li>Red blips indicate an invalid REDACTED packet -> Translation: wtf is this shit</li>
      <li>Blue indicates a web request ->  Translation: fuk off ASSHAT</li>
      <li>Green pulse indicates SWARM MODE -> Translation: stop it turd face</li>
      <li>Blue pulse indicates AUTON. MODE -> Translation: leave me alone butt hole</li>
      <li>Sparkles indicate a good time -> Tanslation: v=wKfMZOR8eWI</li>
    </ul></ul>&nbsp;&nbsp;
    
    <h3>ROBOTS TRANSCLUSIVE XENOMORPHIC TRANSCRIPTOR - HUMAN INTERACTION CONTROL SCHEME (R.TXT-HICS) ERROR CODES:</h3>
    <ol><ol>
      <li>WATCH MORE YOUTUBE</li>
      <li>ASK CHATGPT</li>
      <li>REDACTED (For the current broadcasted REDACTED, see the REDACTED)</li>
    </ol></ol>&nbsp;&nbsp;

    <h3>Included in the sparkly bag:</h3>
    <ul><ul>
      <li>1x SECURE A.S.S. BADGE</li>
      <li>1x Antenna</li>
      <li>3x AAA Batteries</li>
      <li>1x Lanyard</li>
      <li>1x Maybe some other stuff... Maybe it's a Flag.</li>
    </ul></ul>&nbsp;&nbsp;
    
    <h3>I can't find the things...</h1>
    <ul><ul>
        <li>Read the readme again.</li>
        <li>Check the github page</li>
        <li>Find the console at <a href="http://192.168.4.1/">http://192.168.4.1/</a>.</li>
        <li>Try Harder.</a><a href="https://secureassbadge.github.io/static/" style="color: black;text-decoration: none;">.</a><a href="https://github.com/SecureASSBadge/secureassbadge.github.io" style="color: black;text-decoration: none;">.</a></li>
    </ul></ul>
    &nbsp;
    <p>If you need help, look for us in the DEF CON 31 CONTEST area. No promises.</p>&nbsp;&nbsp;
  </div>

  <div id="credit">
    <h1>Credit</h1>
    <p>blametheotherkyle</p>
    <p>Petpika</p>
  </div>&nbsp;&nbsp;

  <div id="license">
    <h1>LICENSE</h1>
    <p>ILLEGAL TO SELL ON EBAY</p>&nbsp;&nbsp;
    <p>The SECURE A.S.S. BADGE and any ROBOT FRIEND are provided 'as is' and any express or implied warranties, including, but not limited to, implied warranties of merchantability, of satisfactory quality, non-infringement of third party rights, and fitness for a particular purpose or use are disclaimed in respect of any source or product to the maximum extent permitted by law. In no event and under no legal theory, whether in tort (including negligence), contract, or otherwise, unless required by applicable law (such as deliberate and grossly negligent acts) or agreed to in writing, shall any creator be liable to You for damages, including any direct, indirect, special, incidental, or consequential damages of any character arising as a result of this License or out of the use or inability to use the Work (including but not limited to damages for loss of goodwill, work stoppage, computer failure or malfunction, or any and all other commercial damages or losses), even if such 1337 h@x0r has been advised of the possibility of such damages.</p>
    &nbsp;&nbsp;
  </div>
</div>

)rawliteral";

/*
    <h3>How do you get one?</h3>
    <ol><ol>
      <li>Purchase at Hacker Warehouse in the DC31 VENDORS area</li>
      <li>Look for (free) drops on #badgelife</li>
      <li>Trade (find us at the DEF CON 31 CONTEST area or BSidesLV Pool Lounge - probably drunk).</li>
    </ol></ol>&nbsp;&nbsp;*/

const char robots[] PROGMEM = R"rawliteral(
USER-AGENT: SECURE-ASS
DISALLOW: /admin.php
R.TXT.HICS: KILLALLHUMANS
)rawliteral";

#endif // ASSHTML_H