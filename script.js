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

document.addEventListener('DOMContentLoaded', initReservationForm);
