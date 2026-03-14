function initReservationForm() {
  const form = document.getElementById('reservationForm');
  const status = document.getElementById('reservationStatus');
  if (!form || !status) return;

  form.addEventListener('submit', (event) => {
    event.preventDefault();
    const data = new FormData(form);
    const name = data.get('name');
    const date = data.get('date');
    const time = data.get('time');

    status.textContent = `Thank you, ${name}. Your reservation request for ${date} at ${time} has been received. Our team will confirm shortly by phone.`;
    form.reset();
  });
}

function initMobileNav() {
  const toggle = document.querySelector('.nav-toggle');
  const links = document.querySelector('.nav-links');
  if (!toggle || !links) return;

  toggle.addEventListener('click', () => {
    const isOpen = links.classList.toggle('open');
    toggle.setAttribute('aria-expanded', String(isOpen));
  });

  links.querySelectorAll('a').forEach((a) => {
    a.addEventListener('click', () => {
      links.classList.remove('open');
      toggle.setAttribute('aria-expanded', 'false');
    });
  });
}

document.addEventListener('DOMContentLoaded', () => {
  initReservationForm();
  initMobileNav();
});
