// Este archivo se utilizará para futuras funcionalidades de JavaScript.
document.addEventListener('DOMContentLoaded', function () {
    // Ejemplo: Animación suave al hacer scroll hacia un ancla
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();

            document.querySelector(this.getAttribute('href')).scrollIntoView({
                behavior: 'smooth'
            });
        });
    });

    // Elementos del DOM
const chatbotToggle = document.getElementById('chatbotToggle');
const chatbotContainer = document.getElementById('chatbotContainer');
const chatbotMessages = document.getElementById('chatbotMessages');
const userInput = document.getElementById('userInput');
const sendButton = document.getElementById('sendButton');
const chatbotClose = document.getElementById('chatbotClose')

// Alternar visibilidad
chatbotToggle.addEventListener('click', () => {
  chatbotContainer.classList.toggle('active');
  chatbotToggle.classList.toggle('active');
  if (chatbotContainer.classList.contains('active')) {
    userInput.focus();
  }
});

//Cerrar con la x
chatbotClose.addEventListener('click', () => {
  chatbotContainer.classList.remove('active');
  chatbotToggle.classList.remove('active');
});

// Enviar mensaje
function sendMessage() {
  const rawMessage = userInput.value.trim();
  if (rawMessage === '') return;

  // Normalizamos antes de enviar al C (quita acentos/ñ, minúsculas se manejan en C)
  const message = normalizar(rawMessage);

  addMessage(rawMessage, 'user'); // mostramos lo que escribió el usuario
  userInput.value = '';

  setTimeout(() => {
    if (!wasmReady || !responderFn) {
      addMessage("Estoy cargando mi cerebro en C... intenta de nuevo en unos segundos.", 'bot');
      return;
    }
    const response = responderFn(message);
    addMessage(response, 'bot');
  }, 300);
}

//Agregar mensaje
function addMessage(text, sender) {
  const div = document.createElement('div');
  div.classList.add('message', sender === 'user' ? 'user-message' : 'bot-message');
  
  if (sender === 'bot') {
    div.innerHTML = text; 
  } else {
    div.textContent = text; 
  }

  chatbotMessages.appendChild(div);
  chatbotMessages.scrollTop = chatbotMessages.scrollHeight;
}

// Eventos
sendButton.addEventListener('click', sendMessage);
userInput.addEventListener('keypress', (e) => {
  if (e.key === 'Enter') sendMessage();
});

// Función de normalización 
function normalizar(texto) {
  return texto
    .normalize("NFD")        
    .replace(/[̀-ͯ]/g, "") 
    .replace(/ñ/g, "n")
    .replace(/Ñ/g, "n");
}
}); 