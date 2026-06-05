function mensaje() {
    const quierePromo = confirm(
        "🎉 ¡PROMO DE LA SEMANA EN D'ROSSY! 🎉\n\n" +
        "• 2 Cheesecakes por solo S/ 50.00\n" +
        "• En la compra de cualquier Torta, ¡los Cupcakes van con 20% de descuento!\n\n" +
        "¿Te gustaría que nos pongamos en contacto contigo para separar tu promoción?"
    );

    if (quierePromo) {
        const seccionContacto = document.querySelector("#contacto");
        if (seccionContacto) {
            seccionContacto.scrollIntoView({ behavior: "smooth" });
        }
    }
}

window.addEventListener("scroll", function() {
    const navbar = document.querySelector(".navbar");
    
    if (window.scrollY > 50) {
        navbar.style.backgroundColor = "#ea234e";
    } else {
        navbar.style.backgroundColor = "#e32f5c"; 
    }
});

let listaMensajes = JSON.parse(localStorage.getItem("mensajesContacto")) || [];

const formulario = document.querySelector("#formulario");

formulario.addEventListener("submit", function(e) {
    e.preventDefault();

    const inputNombre = formulario.querySelector("input[type='text']");
    const inputCorreo = formulario.querySelector("input[type='email']");
    const txtMensaje = formulario.querySelector("textarea");

    const nuevoMensaje = {
        id: Date.now(),
        nombre: inputNombre.value.trim(),
        correo: inputCorreo.value.trim(),
        mensaje: txtMensaje.value.trim(),
        fecha: new Date().toLocaleString()
    };
    listaMensajes.push(nuevoMensaje);

    localStorage.setItem("mensajesContacto", JSON.stringify(listaMensajes));

    // Feedback visual al usuario
    alert(`¡Gracias ${nuevoMensaje.nombre}! Mensaje enviado correctamente ✅`);

    formulario.reset();

    console.log("Mensajes guardados actualmente:", listaMensajes);
});